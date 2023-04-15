#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void* hello_world(void* arg)
{
    printf("hello world\n");
    pthread_exit(NULL);   //结束线程
}

int main()
{
    pthread_t thread;
    int rc = pthread_create(&thread,NULL,hello_world,NULL);
    if(rc)
    {
        printf("Error creating thread\n");
        exit(-1);
    }
    pthread_join(thread,NULL); //回收子线程

    return 0;
}
