#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void sys_err(const char* str)
{
    perror(str);
    exit(1);
}


int main(int argc,char * argv[])
{
    int fd[2];
    int ret;
    pid_t pid;
    int i = 0;
    ret = pipe(fd);
    if(ret == -1)
    {
        sys_err("pipe error");
    }

    for(i = 0;i<2;i++)
    {
        //循环创建两个兄弟进程
        pid = fork();
        if(pid == -1)
        {
            sys_err("fork errno");
        }
        if(pid == 0)
            break;
    }

    //想清楚这种方法,兄进程被创建出来以后,break出来了.此时i = 0
    //弟进程被创建出来以后,break出来了,此时i = 1

    if(i == 2)  //父进程
    {
        //这里非常重要!!
        //要把父进程的读和写都给关了,才能保证后面兄弟进程间通信的时候,管道是单向的(只有雨一个进程读,一个进程写)

        close(fd[0]);
        close(fd[1]);
        wait(NULL);
        wait(NULL);
    }
    else if(i == 0)  //兄进程
    {
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        execlp("ls","ls",NULL);
        sys_err("execlp ls error");
    }

    else if(i == 1)  //弟进程
    {
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
        execlp("wc","wc","-l",NULL);
        sys_err("execlp wc error");
    }



}





