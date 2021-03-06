#include <boost/thread.hpp>


#include <iostream>
#include <sched.h>

using namespace std;


void th_func()
{
  cout << "Hello, thread!" << endl;
}

int main(int argc, char **argv) {
    cout << "Hello, world! 1" << endl;
    static boost::thread DummyThr(&th_func);
    cout << "Hello, world! 2" << endl;
    sched_yield();
    sleep( 1 );
    return 0;
}
