#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<errno.h>

int main()
{
    perror(1);
    exit(1);
}

void catch_child(int signo)
{
    pid_t wpid;

    int status;
    while((wpid = waitpid(-1,&status,0)) != -1)
    {
        if(WIFEXITED(status))
            printf("--------------------catch child id %d,ret = %d\n",wpid,WEXITSTATUS(status)+1);
    }

    return;
}

int main()
{
    pid_t pid;

    int i = 0;
    for(i = 0;i<15;i++)
    {
        if((pid = fork())==0)
            break;
    }

    if(i == 15)
    {
        struct sigaction act;

        act.sa_handler = catch_child;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;

        sigaction(SIGCHLD,&act,NULL);

        printf("I'm parent , pid = %d\n",getpid());

        while(1);
    }
    else if(i<0)
        sys_err("fork error");
    else
    {
        printf("I'm child pid = %d\n",i+1);
    }

}






