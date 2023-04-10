#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<error.h>
#include<pthread.h>

void sys_err(const char* str)
{
    perror(str);
    exit(1);
}

void* tfn(void *arg)
{
    printf("thread:pid = %d,tid = %lu\n",getpid(),pthread_self());

    return NULL;
}

int main(int argc,char* argv[])
{
    pthread_t tid;

    printf("main: pid %d , tid = %lu\n",getpid(),pthread_self());

    int ret = pthread_create(&tid,NULL,tfn,NULL);
    if(ret != 0)
    {
        perror("pthread_creat error");
    }
    sleep(1);

    return 0;
}







