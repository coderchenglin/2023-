#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>   //dup,dup2
#include<pthread.h>

#include<fcntl.h>   //open 
#include<sys/types.h>
#include<sys/stat.h>

#include<unistd.h>  // write

//dup  --  复制一个文件描述符
//int dup(int oldfd)   


//dup2 -- 返回newfd   如果oldfd有效,让newfd指向oldfd所指向的文件,并返回newfd
//int dup2(int oldfd, int newfd);





int main(int argc , char* argv[])
{   
    //假设fd1指向test.c   fd2指向test1.c
    int fd1 = open(argv[1],O_RDWR);      //012  ---  3
    int fd2 = open(argv[2],O_RDWR);      //012  ---  4
    //让fd2指向fd1指向的文件
    
    int fdret = dup2(fd1,fd2);    //fd2指向了test.c  //返回给fdret的是fd2
    printf("fdret = %d  fd2 = %d\n",fdret,fd2);  
    
    int ret = write(fd2,"1234567",7);  //写到哪里,内容,多少个符    返回值:是写入的元素个数
    printf("ret = %d\n",ret);

    dup2(fd1,STDOUT_FILENO);  //将屏幕输入,重定向给fd1所指向的文件

    //接下来打印,本应往屏幕上打,改成了往test.c文件里打,这就是重定向的原理
    printf("------------------886\n");


    return 0;
}

//这串代码的最终结果:有3个文件描述符都指向了test.c   文件描述符: 2,3,4


//总结:int newfd = dup2(int oldfd,ingt newfd)
//假设oldfd是指向test.c的,newfd是指向屏幕的,那么这个函数,可以让原本指向屏幕的文件描述符nwefd指向test.c,那么我向屏幕写东西,就变成了向test.c文件里写东西




