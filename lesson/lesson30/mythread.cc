#include <iostream>
#include <cstdio>
#include <cassert>
#include <pthread.h>
#include <unistd.h>

using namespace std;

int g_val = 0;

// std::ostream fun()
std::string fun()
{
    return "我是一个独立的方法";
    // std::iostream myos;
    // myos << "我是一个独立的方法";
    // return myos;
}

// 新线程
void *thread_routine(void *args)
{
    const char *name = (const char *)args;
    while (true)
    {
        fun();
        cout << "我是新线程, 我正在运行! name: " << name << " : "<< fun()  << " : " << g_val++ << " &g_val : " << &g_val << endl;
        sleep(1);
    }
}

int main()
{
    // typedef unsigned long int pthread_t;
    pthread_t tid;
    int n = pthread_create(&tid, nullptr, thread_routine, (void *)"thread one");
    assert(0 == n);
    (void)n;

    // 主线程
    while (true)
    {
        // 地址 -> ?
        char tidbuffer[64];
        snprintf(tidbuffer, sizeof(tidbuffer), "0x%x", tid);
        cout << "我是主线程, 我正在运行!, 我创建出来的线程的tid： " << tidbuffer << " : " << g_val << " &g_val : " << &g_val << endl;
        sleep(1);
    }

    return 0;
}