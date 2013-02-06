/*                               -*- Mode: C -*- 
 * malloc-bench.cc -- benchmark malloc/free in MT code
 *
 * $Id$
 *
 * Creator         : Tom Pavel  <tom>     Thu Sep  8 21:51:12 1994
 * Modifier        : Tom Pavel  <tom>     Thu Sep  8 21:51:29 1994
 * Update Count    : 1
 * Status          : working
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <pthread_np.h>

#include <vector>

#ifndef lint
static char RCSid[] = "$Header$";
#endif 

class Mutex
{
public:
    Mutex()
    {
	pthread_mutex_init(&_mutex, NULL);
    }
    ~Mutex()
    {
	pthread_mutex_destroy(&_mutex);
    }

    void Lock()
    {
	pthread_mutex_lock(&_mutex);
    }
    void Unlock()
    {
	pthread_mutex_unlock(&_mutex);
    }

public:
    // public so as to friend w/ CV
    pthread_mutex_t _mutex;
};

class CV
{
public:
    CV(Mutex& m) :
	    _m(m)
    {
	pthread_cond_init(&_cv, NULL);
    }
    ~CV()
    {
	pthread_cond_destroy(&_cv);
    }

    void Wait()
    {
	pthread_cond_wait(&_cv, &_m._mutex);
    }
    void Signal()
    {
	pthread_cond_signal(&_cv);
    }
    void Broadcast()
    {
	pthread_cond_broadcast(&_cv);
    }
private:
    pthread_cond_t _cv;
    Mutex& _m;
};

class Thread
{
public:
    Thread(int i, void* (*f)(void*), int N) :
	    _func(f), _index(i), _arg(N)
    {
	pthread_attr_init(&_tattr);
	pthread_attr_setdetachstate(&_tattr, PTHREAD_CREATE_DETACHED);
	//pthread_attr_setscope (&_tattr, PTHREAD_SCOPE_PROCESS);
    }
    ~Thread()
    {
    }

    void setName( const char * name )
    {
	pthread_set_name_np( _thread, name );
    }

    void Run()
    {
	pthread_create(&_thread, &_tattr, _func, this);
    }

    int getIndex() const
    {
	return _index;
    }
    int getArg() const
    {
	return _arg;
    }

private:
    pthread_t _thread;
    pthread_attr_t _tattr;
    void* (*_func)(void*);
    int _index;
    int _arg;
};

class Timer
{
public:
    Timer()
    {
	_start.tv_sec = _start.tv_nsec = 0;
	_stop.tv_sec = _stop.tv_nsec = 0;
    }
    ~Timer()
    {
    }

    void Start()
    {
	clock_gettime(CLOCK_REALTIME, &_start);
    }
    void Stop()
    {
	clock_gettime(CLOCK_REALTIME, &_stop);
    }

    double getStart()
    {
	return _start.tv_sec + _start.tv_nsec * 1e-9;
    }
    double getStop()
    {
	return _stop.tv_sec + _stop.tv_nsec * 1e-9;
    }
    double getDiff()
    {
	return (_stop.tv_sec - _start.tv_sec)
		+ (_stop.tv_nsec - _start.tv_nsec) * 1e-9;
    }

private:
    struct timespec _start;
    struct timespec _stop;
};

// globals
std::vector<Timer> _timers;
int _running = 0;
Mutex _lock;
CV _cond(_lock);

void Usage(const char* progname)
{
    (void) fprintf(stderr, "usage: %s <num-threads> <num-loop>\n", progname);
    exit(EXIT_FAILURE);
}

void*
work(void* arg)
{
    Thread* t = reinterpret_cast<Thread*>(arg);
    int i = t->getIndex();
    int N = t->getArg();
    const int loop = 10 * 1024;
    const size_t MY_SIZE = 128;
    char* p[loop];

    _timers[i].Start();
    while (N > 0)
    {
	// split up allocs/frees into separate loops
	for (int x = 0; x < loop; ++x)
	{
	    p[x] = (char*) malloc(MY_SIZE);
	    p[x][0] = '\000'; //optional touch mem
	}
	for (int x = 0; x < loop; ++x)
	{
	    free(p[x]);
	    --N;
	}
    }
    _timers[i].Stop();

    // decrement to say we're done
    _lock.Lock();
    if (--_running == 0)
    {
	// wakeup the parent (if we're the last)
	_cond.Signal();
    }
    _lock.Unlock();
    return 0;
}

int main(int argc, const char** argv)
{
    bool do_threads = true;
    char thread_name[128];

    if (argc != 3)
    {
	Usage(argv[0]);
	return 1; // Usage() doesn't return
    }

    int nthrd = atoi(argv[1]);
    int N = atoi(argv[2]);
    if (*argv[1] == '0')
    {
	// special signal value
	do_threads = false;
    }
    else if (nthrd <= 0 || N <= 0)
    {
	Usage(argv[0]);
	return 1; // Usage() doesn't return
    }

    _timers.resize(nthrd + 1);

    // launch threads
    _timers[0].Start();
    for (int i = 1; i <= nthrd; ++i)
    {
	Thread* t = new Thread(i, work, N / nthrd); // mem leak...
	sprintf( thread_name, "thread%d", i );
	t->Run();
	t->setName( thread_name );
    }

    if (do_threads)
    {

	// wait for all to finish
	_lock.Lock();
	_running = nthrd;
	while (_running > 0)
	    _cond.Wait();
	_lock.Unlock();

    }
    else
    {

	// create a dummy thread and call work directly
	Thread t(0, work, N);
	work(&t);

    }
    _timers[0].Stop();

    // print out results
    double sum = 0.0;
    for (int i = 1; i <= nthrd; ++i)
    {
	double dt = _timers[i].getDiff();
	sum += dt;
	printf("Thread %d - (%f : %f) %f sec - %f nsec/pair\n", i,
		_timers[i].getStart(), _timers[i].getStop(), dt,
		dt / (N / nthrd) * 1e9);
    }
    printf("Proc (wait) time = (%f : %f) %f sec\n", _timers[0].getStart(),
	    _timers[0].getStop(), _timers[0].getDiff());

    if (!do_threads)
    {
	sum = _timers[0].getDiff();
	nthrd = 1;
    }
    printf("Avg thread time = %f sec - %f nsec/pair\n", sum / nthrd,
	    sum / N * 1e9);

    return 0;
}
