#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

#include<sys/stat.h>

int main(int argc, char* argv[])
{
    struct stat sb; 

    int ret = stat(argv[1],&sb);  //记住sb是一个传出参数,我们需要的数据都存在其中
    if(ret == -1)
    {
        perror("stat error");
        exit(1);
    }

    if(S_ISREG(sb.st_mode))
    {
        printf("Is's a regular\n"); // 宏函数的返回值通常为0或1
    }
    else if(S_ISDIR(sb.st_mode)) 
    {
        printf("It's a directory\n");
    }
    else if(S_ISFIFO(sb.st_mode))
    {
        printf("It's a pipe\n");
    }
    else if(S_ISLNK(sb.st_mode))
    {
        printf("It's a sym link\n");
    }

}





