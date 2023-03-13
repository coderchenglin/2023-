#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

//管道是所有进程间通信中最容易的
//大致思路就是,两个进程,一个关闭读端只写,另一个关闭写端只读
//(记得读端先把内容读到缓冲区中,再把缓冲区中的内容打印到屏幕上)
//fd[0]是读端,fd[1]是写端

void sys_err(const char*str)
{
    perror(str);
    exit(1);
}

int main(int argc ,char* argv[])
{
    int ret;
    int fd[2]; 
    pid_t pid;

    char* str = "hello pipe\n";
    char buf[1024];

    ret = pipe(fd);
    if(ret == -1)
        sys_err("pipe error");
    

    pid = fork();
    if(pid > 0)
    {
        close(fd[0]);  //父进程关闭读端
        write(fd[1],str,strlen(str));
        sleep(1);  //让父进程睡一秒,保证父进程不会比子进程先结束
        close(fd[1]);
    }
    else if(pid == 0)
    {
        close(fd[1]);  //子进程关闭写端
        ret = read(fd[0],buf,sizeof(buf));  //从读端读进缓冲区buf中
        write(STDOUT_FILENO,buf,ret);  //在把缓冲区中的数据写到屏幕上
        close(fd[0]);
    }

    return 0;
}

/*

管道读写行为:
    读管道:
        1.管道有数据: read返回实际读到的字节数
        2.管道有数据: 1)无写端:read返回0(类似读到文件尾)
                      2)有写端:read等待阻塞 

    写管道:
        1.无读端:异常终止.(SIGPIPE导致)
        2.有读端:1)管道已满,阻塞等待   (不过实际上管道满了会扩容,所以一般见不到)
                 2)管道未满,返回写入的字节个数
*/




