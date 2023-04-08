#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

//练习使用kill系统调用
//int kill(pit_t pid,int sig)

int main()
{
    pid_t pid = fork();

    if(pid > 0)
    {
        printf("parent , pid = %d\n",getpid());
        while(1);
    }
    else if(pid == 0)
    {
        printf("chiild pid = %d , ppid = %d\n",getpid(),getppid());
        sleep(2);
        kill(getppid(),SIGSEGV);  //段错误信号
        //kill(0,SIGKILL)         //0代表发送信号给：发送信号的这个进程所在的进程组
        //如果传-1，代表发送给进程有权限发送的系统中所有的进程（诛杀），不属于同意进程组的也可以

       //命令：kill -9 -10879    //进程编号前面带一个负号，表示，发送给这个进程组
        //通常父进程创建的子进程，同属于同一个进程组
        //
    }

    return 0;
}





