#include<stdio.h>
#include<unistd.h>


int main()
{
    while(1)
    {
        printf("我是一个进程,我的id是:%d,我的ppid是%d\n",getpid(),getppid());
        sleep(1);
    }
    return 0;
}

