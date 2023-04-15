#include<stdio.h>
#include<std;ib.h>
#include<pthread.h>


pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void* thread1(void* arg)
{
    //线程1获取锁1
    pthread_mutex_lock(&lock1);
    printf("Thread 1 acquired lock 1\n");

    printf("Thread 1 tries to acquire lock 2\n");
    pthread_mutex_lock(&lock2);
    printf("Thread 1 acquired lock 2\n");

    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
    return NULL;
}

void* thread2(void* arg)
{
    pthread_mutex_lock(&lock2);
    printf("Thread 2 acquired lock 2\n");

    printf("Thread 2 tries to acquire lock 1\n");
    pthread_mutex_lock(&lock1);
    printf("Thread 2 acquired lock 1\n");

    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
    return NULL;
}

int main()
{
    pthread_t t1,t2;

    pthread_create(&t1,NULL,thread1,NULL);
    pthread_create(&t2,NULL,thread2,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    return 0;
}





