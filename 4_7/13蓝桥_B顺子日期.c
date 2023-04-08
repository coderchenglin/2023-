#include<stdio.h>
#include<stdbool.h>


const int months[] = {0.31,28,31,30,31,30,31,31,30,31,30,31};

bool check(char str[],int len)
{
    int i = 0;
    for(i = 0;i+2<len;i++)
        if(str[i+1] == str[i] + 1 && str[i+2] == str[i] +2)
            return true;
    return false;
}

int main()
{
    int year = 2022,month = 1,day = 1;

    int res = 0;
    int i = 0;
    for(int i = 0;i<365;i++)
    {
        char str[10];
        sprintf(str,"%04d%02d%02d",year,month,day);
        int len = sizeof(str);
        if(check(str,len))
        {
            res++;
        }

        if( ++day > months[month])
        {
            day = 1;
            month++;
        }

    }
    printf("%d\n",res);

    return 0;
}



