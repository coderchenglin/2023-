#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// volatile: 保持内存可见性！
// volatile int quit = 0;

void handler(int signo)
{
    // 1. 我有非常多的子进程，在同一个时刻退出了

    // waitpid(-1) -> while(1)
    // 2. 我有非常多的子进程，在同一个时刻只有一部分退出了
    // while(1)
    // {
    //     pid_t ret = waitpid(-1, NULL, WNOHANG);
    //     if(ret == 0) break;
    // }

    // printf("pid: %d, %d 号信号，正在被捕捉!\n", getpid(), signo);
    // printf("quit: %d", quit);
    // quit = 1;
    // printf("-> %d\n", quit);
}

void Count(int cnt)
{
    while (cnt)
    {
        printf("cnt: %2d\r", cnt);
        fflush(stdout);
        cnt--;
        sleep(1);
    }
    printf("\n");
}

int main()
{
    // 显示的设置对SIGCHLD进行忽略
    signal(SIGCHLD, SIG_IGN);
    signal(SIGCHLD, SIG_DFL);

    printf("我是父进程, %d, ppid: %d\n", getpid(), getppid());

    pid_t id = fork();
    if (id == 0)
    {
        printf("我是子进程, %d, ppid: %d，我要退出啦\n", getpid(), getppid());
        Count(5);
        exit(1);
    }

    while (1)
        sleep(1);

    // signal(2, handler);
    // while(!quit);
    // printf("注意， 我是正常退出的!\n");
    return 0;
}

// #include <iostream>
// #include <cstdio>
// #include <signal.h>
// #include <unistd.h>

// using namespace std;

// void Count(int cnt)
// {
//     while(cnt)
//     {
//         printf("cnt: %2d\r", cnt);
//         fflush(stdout);
//         cnt--;
//         sleep(1);
//     }
//     printf("\n");
// }

// void handler(int signo)
// {
//     cout << "get a signo: " << signo << "正在处理中..." << endl;
//     Count(20);
// }

// int main()
// {
//     struct sigaction act, oact;
//     act.sa_handler = handler;
//     act.sa_flags = 0;
//     sigemptyset(&act.sa_mask); // 当我们正在处理某一种信号的时候，我们也想顺便屏蔽其他信号，就可以添加到这个sa_mask中
//     sigaddset(&act.sa_mask, 3);
//     sigaction(SIGINT, &act, &oact);

//     while(true) sleep(1);

//     return 0;
// }