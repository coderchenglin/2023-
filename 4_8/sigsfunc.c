#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<errno.h>


void print_set(sigset_t* set)
{
    int i = 0;
    for(i = 0;i<32;i++)
    {
        if(sigismember(set,SIGINT))  //这个函数，用于判断信号
            putchar('1');
        else
            putchar('0');
    }
    printf("\n");
}

int main()
{
    sigset_t set,oldset,pedset;

    int ret = 0;

    sigemptyset(&set);       //信号集操作函数
    sigaddset(&set,SIGINT);  //信号集操作函数

    ret = sigprocmask(SIG_BLOCK,&set,&oldset);  //用于操作进程信号屏蔽字的函数
    if(ret == -1)
    {
        perror("sigprocmask error");
        exit(1);
    }

    ret = sigpending(&pedset);   //这里是一个传出参数，这个pedset和前面我们自己定义和设置的set不是同一个，这是一个新的sigset_t类型的变量
    if(ret == -1)
    {
        perror("sigpending error");
        exit(1);
    }
    while(1)
    {
        sleep(1);
        print_set(&pedset);  //和sigpending函数配合，打印那个位图
    }

    return 0;
}









