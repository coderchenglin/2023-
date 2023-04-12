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

void* tfn(void* arg)
{
    int i= (int)arg;  //用的时候再把(void*)类型的形参arg，强转会int类型
    sleep(i);

    if(i == 2)
    {
//        exit(0);     //这个不行，exit（0）表示直接退出进程
//        return NULL;    //这个可以，return 表示返回到调用者那里去
    pthread_exit(NULL);
    }
    printf("----I'm %dth pthread: pid = %d , tid = %lu\n",i+1,getpid(),pthread_self());
    return NULL;
}


int main(int argc,char* argv[])
{
    int i;
    int ret;
    pthread_t tid;

    for(i = 0;i<5;i++)
    {
        ret = pthread_create(&tid,NULL,tfn,(void *)i);//传的时候传（void*）类型，所以要将i强转成 void* 类型
        if(ret != 0)                         //注意！ ： 这个地方，只能用传值，不能传址
        {
            perror("pthread_create error");
        }
    }

    sleep(i);
    printf("main: I'm Main,pid = %d,tid = %lu\n",getpid(),pthread_self());

    return 0;
}







