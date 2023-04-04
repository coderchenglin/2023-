#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/wait.h>

void sys_err(const char* str)
{
    perror(str);
    exit(1);
}

int main()
{
    int fd[2];
    int ret;
    int i;
    pid_t pid;

    ret = pipe(fd);   //fork出来的进程，共享文件描述符   pipe函数作用：创建，并打开！管道
                      //name接下来fork出来的所有进程，包括父进程和所有子进程，都打开了这个管道的读端和写端
    if(ret == -1)
    {
        sys_err("pipe error");
    }

    for(i = 0;i<2;i++)
    {
        pid = fork();
        if(pid == -1)
            sys_err("fork error");
        if(pid == 0)
            break;
    }

    if(i == 2)
    {
        close(fd[1]);
        close(fd[0]);
        wait(NULL);
        wait(NULL);
    }
    else if(i == 0)
    {    //读
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
        execlp("wc","wc","-l",NULL);
        sys_err("execlp wc error");
    }
    else if(i == 1)
    {   //写
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        execlp("ls","ls",NULL);
        sys_err("execlp ls error");
    }


    return 0;
}
