#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/time.h>


void myfunc(int signo)
{
    printf("hello world\n");
}

int main()
{
    struct itimerval newit,oldit;

    signal(SIGALRM,myfunc);

    newit.it_value.tv_sec = 2;
    newit.it_value.tv_usec = 0;

    newit.it_interval.tv_sec = 5;
    newit.it_interval.tv_usec = 0;

    if(setitimer(ITIMER_REAL,&newit,&oldit) == -1)
    {
        perror("setitimer error");
        return -1;
    }

    while(1);

    return 0;
}




