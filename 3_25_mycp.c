#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>


int main(int argc,char**argv)
{
    int fd1,fd2;
    fd1 = open(argv[1],O_RDONLY);
    fd2 = open(argv[2],O_RDWR|O_TRUNC|O_CREAT,0664);
    int n;
    char buf[1024];

    while(n = read(fd1,buf,1024))
    {
        write(fd2,buf,n);
    }

    close(fd1);
    close(fd2);

}


//总结:记下几个函数和宏函数对应的头文件
//记下read函数和write函数以及open函数几个参数的用法
//学会边读边写的while循环
//记得一定要关闭文件


