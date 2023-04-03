#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

//主要使用的两种：execl execlp
//l : list      命令行参数列表
//p : path      搜索file时使用path环境变量
//v ： vector   使用命令行参数数组
//e ： environment  使用环境变量数组，不适用金恒原有的环境变量，设置新加载程序运行的环境变量
//
//事实上，只有execve是真正的系统调用，其他5个都是库函数

int main()
{
    char* argv[] = {"ls","-l","-a",NULL};
    execvp("ls",argv);


    return 0;
}


