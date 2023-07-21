#include<stdio.h>
#include<string.h>
#include<unistd.h>


int main()
{
    printf("hello printf\n");
    fprintf(stdout,"hello fputs\n");
    const char* fputsString = "hello fputs\n";
    fputs(fputsString,stdout);


    const char* wstring = "hello write\n";
    write(1,wstring,strlen(wstring));

    fork();

    return 0;
}

//为什么,./myfile,只打印4条信息   而./myfile > test.txt后,会向文件打印7条信息?

/*
为什么会输出两次?
我的回答:
    write的系统调用接口,绕过语言级别缓冲区
而另外三个函数是c接口,使用语言级别缓冲区(即FILE结构体中的缓冲区)

为什么直接执行程序时,不会打印两次,而重定向到文件时,会打印两次?
    直接执行程序时,我们打印到屏幕上(即stdout上),采用的是行缓冲,那一行代码执行完,直接就打印到屏幕上了,进程结束时,缓冲区里实名都没有
而重定向到文件中时,我们是打印到文件(即磁盘设备)上,采用的是全缓冲,这个时候\n就没有用了! write系统调用依然是直接打印到屏幕上(重定向了所以打到文件里了),而3个c接口的数据没有还在缓冲区里(因为是全缓冲!),他们要想刷新只能等另一种特殊情况->进程退出. 而在进程退出前,我们调用了fork函数,子进程拷贝了一份父进程的文件描述符(FILE结构体),缓冲区就在FILE结构体中,也就是说, 子进程拷贝了一份父进程的标准输出缓冲区!!!当进程结束时,子进程会尝试刷新缓冲区上的内容到文件中,这时发生了写时拷贝(进程具有独立性,不会影响父进程!),子进程刷新后,父进程的缓冲区上依然有内容,当父进程结束后,父进程也会刷新一次缓冲区,将内容刷新到文件中. 因此!内容就会被打印两次!
*/
