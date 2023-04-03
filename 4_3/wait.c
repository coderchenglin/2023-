#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

//如何使用wait函数？
//首先定义一个整形传出参数(位图）int status，和一个wpid接受返回值（回收的进程id）
//wpid = wait（&status）;
//接着使用各种宏函数WIFEXITED(status)    WEXITSTATUS(status)    WIFSIGNALED(status)      WTERMSIG(status)
//
//当然，如果不关心死亡状态，可以直接传参数NULL

int main()
{
    pid_t pid,wpid;
    int status;

    pid = fork();
    if(pid == 0)
    {
        printf("---child, my id = %d,going to sleep 3s\n",getpid());
        sleep(3);
        printf("-------child die--------\n");
        return 0;
    }
    else if(pid > 0)
    {
        //wpid = wait(NULL);   //不关心子进程怎么死的
        wpid = wait(&status);
        if(wpid == -1)
        {
            perror("wait error");
            exit(1);
        }
        if(WIFEXITED(status))
        {
            printf("child exit with %d\n",WEXITSTATUS(status));
        }
        if(WIFSIGNALED(status))
        {
            printf("child kill with signal %d\n",WTERMSIG(status));
        }


    }


    return 0;
}





