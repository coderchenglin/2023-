#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>   //dup,dup2
#include<pthread.h>

#include<fcntl.h>
#include<unistd.h>   //fork


int main(int argc , char* argv[])
{
    pid_t pid = fork();
    if(pid == -1)
    {
        perror("fork error");
        exit(1);
    }

    else if(pid == 0)
    {
        char* argv[] = {"ls","-l","-h",NULL};
    }

    execvp("ls",argv);

    perror("exec error");
    exit(1);
    

    else if(pid >0)
    {
        sleep(1); //父进程sleep一秒,可以保证子进程先执行
        printf("I'm parent : %d\n",getpid());
    }




    return 0;
}


//总结,fcntl函数使用F_DUPFD参数时,跟dup函数功能一样,只是后面可用选择返回(使用)哪一个文件描述符,如果指定的文件描述符(假设是7),被占用,则返回一个>=7的文件描述符





