#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>


int main()
{
    pid_t pid,wpid;
    int status;
    int i;

    for(i = 0;i<3;i++)
    {
        pid = fork();
        if(pid == 0)
            break;
    }
    if(i == 0)
    {
        execlp("ps","ps","-axj",NULL);
    }
    if(i == 1)
    {
        execl("./normal","./a.out",NULL);
    }
    if(i == 2)
    {
        execl("./unnormal","./unnoermal",NULL);
    }
    if(i == 3)
    {
        while((wpid = waitpid(-1,NULL,WNOHANG))!=-1)
        {
            if(wpid>0)
            {
                printf("wait the child , pid = %d\n",wpid);
            }
            else if(wpid == 0)
                sleep(1);
                continue;
        }
    }



    return 0;
}




