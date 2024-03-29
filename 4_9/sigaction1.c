#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<errno.h>


void sys_err(const char* str)
{
    perror(str);
    exit(1);
}


void catch_child(int signo)
{
    pid_t wpid;

    int status;
    //此处应该使用循环回收子进程，因为当同一时间内，好几个子进程同时死亡，同时发信号给父进程，父进程只会处理其中一个
    //这样其他未被回收的子进程，就会成为僵尸进程
//    while((wpid = wait(NULL)) !=-1)
    while((wpid = waitpid(-1,&status,0)) != -1)
    {
        if(WIFEXITED(status)) //如果是正常退出的话
            printf("----------------------catch child id %d，ret = %d\n",wpid,WEXITSTATUS(status)+1);
    }




    return;
}

int main()
{
    pid_t pid;

    int i;
    for(i = 0;i<15;i++)
    {
        if((pid = fork())==0)
           break;
    }

    if(i == 15)
    {
        struct sigaction act;

        act.sa_handler = catch_child;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;

        sigaction(SIGCHLD,&act,NULL);

        printf("I'm parent , pid = %d\n",getpid());

        while(1);
    }
    else if(i<0)
        sys_err("fork error");
    else
    {
        printf("I,m child pid = %d\n",i+1);
    }


}





