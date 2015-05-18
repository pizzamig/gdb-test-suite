#include<pthread.h>
#include<unistd.h>

const int threadCount = 4;
pthread_t tid[threadCount];

void* doSomeThing(void *arg)
{
    unsigned long i = 0;
    pthread_t id = pthread_self();

    for(i=0; i<(0xFFFFFFFF);i++);
      sleep(1);

    return NULL;
}

int main(void)
{
    int i;

    for (i = 0; i < threadCount; i++)
        pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);

    sleep(500);

    return 0;
}
