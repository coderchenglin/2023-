#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>   //dup,dup2
#include<pthread.h>

#include<fcntl.h>
#include<unistd.h> 


int main(int argc , char* argv[])
{
    int fd1 = open(argv[1],O_RDWR);

    printf("fd1 = %d\n",fd1);

    int newfd = fcntl(fd1,F_DUPFD,0);  //因为0已经被占用,fcntl使用文件描述符表中可用的最小文件描述符返回
    printf("newfd = %d\n",newfd);


    int newfd1 = fcntl(fd1,F_DUPFD,7);  //因为7没有被占用,所以返回文件描述符7
    printf("newfd1 = %d\n",newfd1);

    int ret = write(newfd1,"YYYYYY",6);
    printf("ret = %d\n",ret);

    return 0;
}


//总结,fcntl函数使用F_DUPFD参数时,跟dup函数功能一样,只是后面可用选择返回(使用)哪一个文件描述符,如果指定的文件描述符(假设是7),被占用,则返回一个>=7的文件描述符






