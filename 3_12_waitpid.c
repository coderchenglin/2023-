#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


int main()
{
    int i = 0;
    pid_t pid,wpid,tmpid;

    for(i = 0;i<5;i++)
    {
        pid = fork();
        if(pid == 0)
        {
            break;
        }
        if(i == 2)
        {
            tmpid = pid;
            printf("----pid = %d\n",pid);
        }
    }
    if(5 == i)  //父进程
    {
        sleep(5);  //等子进程都结束了再回收

      //  wait(NULL);   //一次wait/waitpid函数调用,只能回收一个子进程
      //   wpid =  waitpid(-1,NULL,WNOHANG);   //回收任意子进程,没有结束的子进程,父进程直接返回0
        printf("-----in parent , before waitpid,pid = %d\n",tmpid);
        wpid = waitpid(tmpid,NULL,0); //指定一个进程回收 ,如果加了WNOHANG这个参数,而下标为2的子进程sleep了没结束,那么就没法回收
        if(wpid == -1)
        {
            perror("waitpid error");
            exit(1);
        }
        printf("I'm parent,wait a child finish: %d \n",wpid);  //如果回收失败.会返回0
    }
    else 
    {
        sleep(i);
        printf("I'm %d child,pid = %d\n\n",i+1,getpid());
    }



    return 0;
}



