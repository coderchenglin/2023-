#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


int main()
{
    int i = 0;
    pid_t pid,wpid;

    for(i = 0;i<5;i++)
    {  //创建5个子进程
        pid = fork();
        if(pid == 0)
        {
            break;
        }
    }

    if(5 == i)
    {
        //使用阻塞方式回收子进程
        while((wpid = waitpid(-1,NULL,0)))  //0 -- 阻塞   WNOHANG -- 非阻塞
        {
            printf("wait child %d \n",wpid);
        }
        printf("I'm parent, wait a child finish: %d \n",wpid);

        //使用非阻塞方式回收子进程
        while((wpid = waitpid(-1,NULL,WNOHANG)) !=-1 )  //-1 表示无差别回收
        {
            if(wpid > 0)
            {
                printf("wait child %d \n",wpid);
            }
            else if(wpid == 0)
            {
                sleep(1);
                continue;
            }
        }
    }
    else 
    {
        sleep(i);
        printf("I'm %d child = %d\n",i+1,getpid());
    }



    return 0;
}



