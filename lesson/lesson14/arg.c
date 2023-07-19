#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char* argv[])
{
    if(argc != 2)
    {
        printf("Usge : \n\t%s [-a/-b/-c/-ab/-ac/-bc/-abc]\n",argv[0]);
        return 1;
    }

    if(strcmp("-a",argv[1]) == 0)
    {
        printf("功能a\n");
    }
    if(strcmp("-b",argv[1]) == 0)
    {
        printf("功能b\n");
    }



    return 0;
}



