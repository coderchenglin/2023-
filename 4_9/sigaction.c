#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>


void sys_err(const char* arr)
{
    perror(arr);
    exit(1);
}

void sig_catch(int signo)
{
    printf("catch you!! %d\n",signo);

    return;
}


int main()
{
    struct sigaction act,oldact;
    act.sa_handler = sig_catch;       //设置回调函数
    sigemptyset(&(act.sa_mask));        //操作这个集合，要用专用的函数，而不是用赋值的方法（设置mask，只在回调函数工作期间有效）
    act.sa_flags = 0;                //这个参数通常传0，表示执行默认值

    int ret = sigaction(SIGINT,&act,&oldact);
    if(ret == -1)
        sys_err("sigaction error");

    while(1);

    return 0;
}










