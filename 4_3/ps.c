#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    int fd;
    fd = open("ps.txt",O_RDWR|O_CREAT|O_TRUNC,0666);
    pid_t pid;
    pid = fork();
    if(pid < 0)
    {
        perror("fork error");
    }
    else if(pid == 0)
    {
        dup2(fd,1);
        execlp("ps","ps","-axj",NULL);
    }
    else
    {
        sleep(1);
        printf("I'm parent\n");
    }




    return 0;
}
