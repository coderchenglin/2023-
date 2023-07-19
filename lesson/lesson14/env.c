#include<stdlib.h>
#include<stdio.h>


int main(int argc,char* argv[],char* env[])
{
    /*
    int i = 0;
    for(i = 0; env[i];i++)
    {
        printf("env[%d]:%s\n",i,env[i]);
    }
    */

    extern char** environ;
    int i = 0;
    for(i = 0;environ[i];i++)
    {
        printf("%d:%s\n",i,environ[i]);
    }

}


