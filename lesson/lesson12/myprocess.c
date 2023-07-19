#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    pid_t id = fork();
    if(id == 0)
    {
        //child
        printf("I am child process,pid :%d,ppid:%d\n",getpid(),getppid());
        sleep(5);
        exit(1);
    }
    else 
    {
        //parent 
        while(1)
        {
            printf("I am parent process,pid:%d,ppid:%d\n",getpid(),getppid());
            sleep(1);
        }
    }


    return 0;
}
