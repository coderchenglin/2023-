#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>


//demo内容:ls | wc -l


void sys_err(const char* str)
{
    perror(str);
    exit(1);
}



//可以让父进程去执行wc -l  ;  子进程去执行ls
//这样父进程就不可能比子进程先执行玩

int main(int argc,char* argv[])
{
    //dup2 fork pipe execlp(执行系统函数) 
    //数据从ls流入管道,然后从管道流出到wc         
    //先创建管道,

    //创建一个管道
    int fd[2];
    int ret;

    ret = pipe(fd);
    if(ret == -1)
    {
        sys_err("pipe error");
    }
    
    pid_t pid;
    pid = fork();
    if(pid == -1)
    {
        sys_err("fork error");
    }
    else if(pid > 0)
    {
        //父进程,执行ls ,关闭读端,讲内容重定向到管道
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        execlp("ls","ls",NULL);
        sleep(1);
        sys_err("exclp ls error");
        //这个close执行不了,因为执行了exec函数成功后,后面的函数就不回来了
        close(fd[1]);
    }
    else if(pid == 0)
    {
        //子进程,关闭写端,
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);  //wc原本默认是从终端(屏幕)读,改成了从管道的读端读
        execlp("wc","wc","-l",NULL);
        sys_err("exclp wc error");
    }


    return 0;
}


