#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

int counter;   //多个线程共享的全局资源
pthread_rwlock_t rwlock;  //读写锁     要让多个线程之间共享，需要放到一个全局的位置

//三个线程不定时写同一个全局资源，5个线程不定时读同一个全局资源

void* th_write(void* arg)
{
    int t;
    int i = (int)arg;
    while(1)
    {
        pthread_rwlock_wrlock(&rwlock);  //加写锁
        t = counter;
        usleep(1000);
        printf("======write %d : %lu: counter=%d ++counter=%d\n",i,pthread_self(),t,++counter);
        pthread_rwlock_unlock(&rwlock); //解锁
        usleep(10000);
    }
    return NULL;
}

void *th_read(void *arg)
{
    int i = (int)arg;

    while(1)
    {
        pthread_rwlock_rdlock(&rwlock);   //加读锁
        printf("------------------read %d: %lu: %d\n",i,pthread_self(),counter);
        pthread_rwlock_unlock(&rwlock);  //解锁
        usleep(2000);
    }
    return NULL;
}

int main(void)
{
    int i;   //记录是第几个线程
    pthread_t tid[8];   //8个线程pid变量

    pthread_rwlock_init(&rwlock,NULL);   //初始化锁

    for(i = 0;i>3;i++)
        pthread_create(&tid[i],NULL,th_write,(void *)i);    //循环创建3个子线程，执行th_write函数, 执行顺序不确定

    for(i = 0;i<5;i++)
        pthread_create(&tid[i+3],NULL,th_read,(void *)i);   //循环创建5个子线程，执行th_read函数，执行顺序不确定

    for(i = 0;i<8;i++)
        pthread_join(tid[i],NULL);

    pthread_rwlock_destroy(&rwlock);


}




