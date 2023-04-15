#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

void err_thread(int ret, char* str)
{
    if(ret != 0)
    {
        fprintf(stderr,"%s:%s\n",str,strerror(ret));
        pthread_exit(NULL);
    }
}

//定义一个链表
struct msg{
    int num;
    struct msg* next;
};

//定义一个头指针
struct msg* head;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  //定义+初始化互斥锁

pthread_cond_t has_data = PTHREAD_COND_INITIALIZER;  //定义+初始化一个条件变量

void* producer(void* arg)
{
    while(1){
    struct msg* mp = (struct msg*)malloc(sizeof(struct msg));

    mp->num = rand()%1000+1;
    printf("--produce %d\n",mp->num);

    pthread_mutex_lock(&mutex);
    mp->next = head;    //头插
    head = mp;
    pthread_mutex_unlock(&mutex);

    pthread_cond_signal(&has_data);       //唤醒阻塞在条件变量has——data上的线程。 即唤醒生产者

    sleep(rand()%3);   //睡个一两秒，消费者获取cpu的几率就会比较大
    }

    return NULL;
}

void* consumer(void* arg)
{
    while(1){

    struct msg* mp;

    pthread_mutex_lock(&mutex);
    if(head == NULL)  //说明没数据，阻塞等待
    {
        pthread_cond_wait(&has_data,&mutex);        //阻塞等待条件变量，解锁
    }                                                //pthread_cond_wait 返回时，重新加锁mutex

    mp = head;
    head = mp->next;

    pthread_mutex_unlock(&mutex);
    printf("-------------------------consumer:%d\n",mp->num);

    free(mp);

    sleep(rand()%3);
    }

    return NULL;
}


int main(int argc,char* argv[])
{
    int ret;
    pthread_t pid,cid;

    srand(time(NULL));  //种一个随机数种子

    ret = pthread_create(&pid,NULL,producer,NULL);  //创建生产者
    if(ret != 0)
        err_thread(ret,"pthread_create producer error");

    ret = pthread_create(&cid,NULL,consumer,NULL);  //创建消费者
    if(ret != 0)
        err_thread(ret,"pthread_create consumer error");

    pthread_join(pid,NULL);
    pthread_join(cid,NULL);

    return 0;
}





