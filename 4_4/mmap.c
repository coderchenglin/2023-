#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/mman.h>

//mmap  ---  共享内存映射。 作用是把一个磁盘上的文件，映射到内存上。  这样就可以使用指针对文件进行访问了。
//在没有映射到内存前，文件只能通过open函数先打开，然后使用read、write函数来进行读写
//所以在文件不方便open打开时，或者方便使用指针进行 读、写 操作时，可以使用mmap函数

//mmap函数有6个参数，稍微记一下
//参1：内存映射首地址，通常传NULL，系统自动在内存上分配空间
//参2：映射的空间大小（<=文件大小）
//参3：文件的保护（读写）权限：PROT_READ  PROT_WRITE
//参4：MAP_SHARED，MAP_PRIVATE   //（对内存进行操作时，文件是否也会被改变）
//参5：文件描述符fd
//参6：偏移量。如果传0，就是整个文件。

//返回值：成功返回映射首地址
//      失败返回MAP_FAILED  （void*)(-1)

//mmap后，记得munmap进行映射回收


int main(int argc,char* argv[])
{
    char* p = NULL;
    int fd;
    //创建并打开文件
    fd = open("test_for_mmap",O_RDWR|O_CREAT|O_TRUNC,0644);
    if(fd == -1)
    {
        perror("open error");
        exit(1);
    }
    //扩展文件大小
    //lseek(fd,10,SEEK_END);   //两个函数等价于 ftruncate()函数
    //write(fd,"\0",1);
    ftruncate(fd,20);   //truncate("test_for_mmap",20);
    int len = lseek(fd,0,SEEK_END);

    p = mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(p == MAP_FAILED)
    {
        perror("mmap error");
        exit(1);
    }

    //使用 p 对文件进行读写操作
    strcpy(p,"hello mmap");   //写操作

    printf("----%s\n",p);       //读操作

    int ret = munmap(p,len);  //回收映射 （类似于malloc函数）
    return 0;
}










