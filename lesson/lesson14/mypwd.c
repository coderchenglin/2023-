#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MYPWD "PWD"

int main()
{
    printf("%s\n",getenv(MYPWD));

    return 0;
}

