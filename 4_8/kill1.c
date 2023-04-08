#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int main()
{
    pid_t pid;
    int i = 0;
    pid_t pidarr[10];
    for(i = 0;i<5;i++)
    {
        pid =  fork();
        pidarr[i] = pid;
        if(pid == 0)
            break;
    }

    if(pid == 0)
    {
        while(1)
        {
            printf("%d\n",i+1);
            sleep(1);
        }
    }
    if(pid > 0)
    {
        sleep(5);
        kill(pidarr[1],SIGKILL);
        sleep(1);
        kill(pidarr[2],SIGKILL);
        sleep(1);
        kill(pidarr[3],SIGKILL);
        sleep(1);
        kill(pidarr[4],SIGKILL);
        sleep(1);
        kill(pidarr[0],SIGKILL);
    }

    return 0;
}









