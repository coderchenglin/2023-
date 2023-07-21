#include "myStdio.h"
#include <stdio.h>

int main()
{
    FILE_ *fp = fopen_("./log.txt","w");
    if(fp == NULL)
    {
        return 1;
    }
    int cnt = 10;
    const char* msg = "hello bit";
    while(1)
    {
        fwrite_(msg,strlen(msg),fp);
        fflush_(fp);
        sleep(1);
        printf("count : %d\n",cnt);

        cnt--;
        if(cnt == 0)
            break;
    }
    fclose_(fp);

    return 0;
}







