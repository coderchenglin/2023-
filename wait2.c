#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
    pid_t pid,wpid;
    int status;

    pid = fork();
    if(pid == 0)
    {
        printf("---child,my id = %d , going to sleep 10s\n",getpid());
        sleep(10);
        printf("--------child die ------\n");
        return 40;
    }
    
    else if(pid >0)
    {
        wpid = wait(&status);
        if(wpid == -1)
        {
            perror("wait error");
            exit(1);
        }
        if(WIFEXITED(status))
        {
            printf("child exit with %d\n",WEXITSTATUS(status));
        }
        if(WIFSIGNALED(status))
        {
            printf("child kill with signal %d\n",WTERMSIG(status));
        }

    }
    else 
    {
        perror("fork error");
        return 1;
    }

}



