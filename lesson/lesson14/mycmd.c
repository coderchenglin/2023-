#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define USER "USER"
#define MY_ENV "myval"

int main()
{
    char* myenv = getenv(MY_ENV);

    if(NULL == myenv)
    {
        printf("%s,not found\n",MY_ENV);
        return 1;
    }
    printf("%s=%s\n",MY_ENV,myenv);

    return 0;
}





/*
int main()
{
    char* who = getenv(USER);

    if(strcmp(who,"root") == 0)
    {
        printf("user:%s\n",who);
    }
    else 
    {
        printf("权限不足!\n");
    }

    return 0;
}
*/ 
