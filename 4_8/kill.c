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
        kill(getppid(),SIGSEGV);
    }

    return 0;
}





