#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

using namespace std;

static void Usage(const std::string &proc)
{
    std::cout << "\nUsage: " << proc << " pid signo\n"
              << std::endl;
}

// int cnt = 0;
void catchSig(int signo)
{
    std::cout << "获取到一个信号，信号编号是: " << std::endl;
    // exit(1);
    // alarm(1);
}
// ./myprocess pid signo
int main(int argc, char *argv[])
{
    


    // for(int signo = 1; signo <= 31; signo++)
    // {
    //     signal(signo, catchSig);
    // }
    // while(true) 
    // {
    //     cout << "我在运行: " << getpid() <<endl;
    //     sleep(1);
    // }
    // 核心转储
    // while (true)
    // {
    //     int a[10];
    //     // a[10000] = 106;
    // }
    // 4. 软件条件 -- "闹钟"其实就是用软件实现的
    // IO其实很慢
    // 统计1S左右，我们的计算机能够将数据累计多少次!
    // signal(SIGALRM, catchSig);
    // alarm(1);
    // while(true)
    // {
    //     cnt++;
    // }
    // 3. 产生信号的方式：硬件异常产生信号
    // 信号产生，不一定非得用户显示的发送！
    // signal(SIGFPE, catchSig);
    // int a = 10;
    // // 如何证明？
    // // 受到信号，不一定会引起进程退出 -- 没有退出，有可能还会被调到
    // // -- CPU内部的寄存器只有一份，但是寄存器中的内容，属于当前进程的上下文！
    // // 你有没有能力或者动作修正这个问题呢？没有
    // // 当进程被切换的时候，就有无数次状态寄存器被保存和回复的过程
    // // 所以每一次恢复的时候，就让OS识别到了CPU内部的状态寄存器中的溢出标志位是1
    // // OS如何得知应该给当前进程发送8号信号的-- OS怎么知道我除0了呢？？，CPU会异常
    // a /= 0; // 为什么除0 会终止进程？当前进程会受到来自OS系统的信号(告知)，SIGFPE
    // signal(11, catchSig);
    // while (true)
    // {
    //     std::cout << "我在运行中...." << std::endl;
    //     sleep(1);
    //     int *p = nullptr;
    //     // p = nullptr; // 1
    //     // OS怎么知道呢？？我野指针了呢？
    //     *p = 100;  //为什么 野指针 就会崩溃呢？因为OS会给当前进程发送指定的11号信号
    // }
    // 2. 系统调用向目标进程发送信号
    // kill()可以想任意进程发送任意信号
    // raise() 给自己 发送 任意信号kill(getpid(), 任意信号)
    // abort() 给自己 发送 指定的信号SIGABRT, kill(getpid(), SIGABRT)
    // 关于信号处理的行为的理解：有很多的情况，进程收到大部分的信号，默认处理动作都是终止进程
    // 信号的意义：信号的不同，代表不同的事件，但是对事件发生之后的处理动作可以一样！
    // int cnt = 0;
    // while(cnt <= 10)
    // {
    //     printf("cnt: %d, pid: %d\n", cnt++, getpid());
    //     sleep(1);
    //     // if(cnt >= 5) abort(); // kill(getpid(), signo)
    //     // if(cnt >= 5) raise(9); // kill(getpid(), signo)
    // }
    // if(argc != 3)
    // {
    //     Usage(argv[0]);
    //     exit(1);
    // }
    // pid_t pid = atoi(argv[1]);
    // int signo = atoi(argv[2]);
    // int n = kill(pid, signo);
    // if(n != 0)
    // {
    //     perror("kill");
    // }
    // 1. 通过键盘发送信号
    // while(true)
    // {
    //     std::cout << "hello world" << std::endl;
    //     sleep(1);
    // }
}