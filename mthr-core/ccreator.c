#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int die = 0;

void *
foo_thread (void *arg)
{
	while (!die)
		sleep(1);
	abort();

	/* Not reached. */
	return (NULL);
}

int
main ()
{
	pthread_t tid;

	pthread_create(&tid, NULL, foo_thread, NULL);
	die = 1;

	while (1)
		sleep(1);

	return (0);
}

