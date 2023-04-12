#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<error.h>
#include<string.h>
#include<malloc.h>

//定义一个结构体
struct thrd{
    int var;
    char str[256];
};


void* tfn(void *arg)   //线程回调函数 的返回值，是一个结构体类型的指针(注意：1.不能是结构体，因为结构体是一个局部变量，要是指针)
{
    struct thrd* tval;   //定义一个结构体指针
    tval =(struct thrd*) malloc(sizeof(tval)); //给他开辟一块空间，变成一个有效的指针
    tval->var = 100;
    strcpy(tval->str,"hello thread");

    return (void*)tval;
}

int main()
{
    pthread_t tid;  //定义一个pthread_t线程id变量
    struct thrd* retval;  //定义一个结构体类型的指针，接收返回值

    int ret = pthread_create(&tid,NULL,tfn,NULL); //创建子线程
    if(ret != 0)
    {
        perror("pthread_create error");
        exit(1);
    }

    ret = pthread_join(tid,(void **)&retval);  //阻塞回收子线程   //返回值是一个void*，一级指针，所以要用一个 二级指针来回收，所以强转成（void**）
    if(ret != 0)
    {
        perror("pthread_join error");
        exit(1);
    }

    printf("child thread exit with var = %d ,str %s\n",retval->var,retval->str);

    pthread_exit(NULL); //退出当前线程(不影响其他线程,包括主线程创建的其他子线程)

    return 0;
}




