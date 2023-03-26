#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

//stat函数中,第二过分参数是一个传出参数

int main(int argc,char* argv[])
{
    struct stat sbuf;  //先创建一个stat结构体类型的结构体
                            
    int ret = stat(argv[1],&sbuf); //buf指向的地址空间有效,但是没有实际意义
    if(ret  == -1)
    {
        perror("stat error");
        exit(1);
    }

    printf("file size:%d\n",sbuf.st_size);  //打印文件大小的正规写法
    return 0;
}

