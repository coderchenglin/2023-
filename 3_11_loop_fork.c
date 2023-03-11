#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>   //dup,dup2
#include<pthread.h>

#include<fcntl.h>
#include<unistd.h>   //fork


int main(int argc , char* argv[])
{
    printf("before fork1---\n");
    printf("before fork2---\n");
    printf("before fork3---\n");
    printf("before fork4---\n");
    printf("before fork5---\n");
    
    pid_t pid = fork();
    if(pid == -1)
    {
        perror("fork error");
        exit(-1);
    }
    else if(pid == 0)
    {
        //子进程
        printf("child,pid = %d  ,ppid = %d\n",getpid(),getppid());
        printf("zi:pid = %d",pid);
    }
    else if(pid >0)
    {
        //父进程
        printf("parent,pid = %d  ,ppid= %d\n",getpid(),getppid());
        printf("fu:pid = %d",pid);
    }

    printf("=======end of file\n");



    return 0;
}


//总结,fcntl函数使用F_DUPFD参数时,跟dup函数功能一样,只是后面可用选择返回(使用)哪一个文件描述符,如果指定的文件描述符(假设是7),被占用,则返回一个>=7的文件描述符





