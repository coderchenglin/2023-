#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>   //fork exec函数族

//ecec函数族，成功没有返回值，失败返回-1
//因为如果执行成功，代码就被替换了，返回值没有意义

//execlp : 通常调用系统命令，因为他参1传的是环境变量，通常我写的a.out不在环境变量中
//execl  ：通常调用自己的可执行文件，因为他参1传的文件路径

int main()
{
    int i;

    for(i = 0;i<5;i++)
    {
        if(fork()==0)
            break;
    }
    if(i == 5)
    {
        sleep(1);
        printf("I'm parent\n");
    }
    if(i == 0)
    {
        printf("I'm %dth child\n",i+1);
        execlp("ls","ls","-l",NULL);
    }

    if(i == 1)
    {
        execl("./test1_hello","./test1_hello",NULL);
        printf("I'm %dth child\n",i+1);
    }
    if(i == 2)
    {
        printf("I'm %dth child\n",i+1);
    }
    if(i == 3)
    {
        printf("I'm %dth child\n",i+1);
    }
    if(i == 4)
    {
        printf("I'm %dth child\n",i+1);
    }


    return 0;
}
