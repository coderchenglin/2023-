#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>   //可有可无
#include<sys/wait.h>

int main()
{
    int status;
    pid_t pid,wpid;
    int i;

    for(i = 0;i<5;i++)
    {
        pid = fork();
        if(pid == 0)
            break;
    }

    if(i == 5)
    {
        while((wpid = waitpid(-1,NULL,WNOHANG)) != -1)
        {
            if(wpid > 0)
            {
                printf("wpid child %d \n",wpid);
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
        printf("I'm %dth child\n",i+1);
    }



    return 0;
}






