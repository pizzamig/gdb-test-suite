#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <pthread_np.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static void *routine (void *arg)
{
  pid_t pid;
  int status;
  printf ("thread started\n");
  pid = fork ();
  if (pid == 0)
  {
    printf ("child started\n");
    sleep (1);
    printf ("child finished\n");
    _exit (0);
  }
  else
  {
    printf ("parent waiting\n");
    wait (&status);
    printf ("child exited\n");
  };
  return NULL;
}

int main ()
{
  pthread_attr_t attr;
  pthread_t thread;

  pthread_attr_init (&attr);
  pthread_create (&thread, &attr, routine, NULL);
  printf ("thread created\n");
  pthread_join (thread, NULL);

  return 0;
}

