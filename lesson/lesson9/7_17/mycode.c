#include<stdio.h>
#include<unistd.h>

int main()
{
    int cnt = 9;
    while(cnt)
    {
        printf("%d\r",cnt);
        fflush(stdout);
        cnt--;
        sleep(1);
    }

    return 0;
}


