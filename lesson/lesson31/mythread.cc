#include <iostream>
#include <unistd.h>
#include <thread>

void thread_run()
{
    while (true)
    {
        std::cout << "我是新线程..." << std::endl;
        sleep(1);
    }
}

int main()
{
    // 任何语言，在linux中如果要实现多线程，必定要是用pthread库
    // 如何看待C++11中的多线程呢？？C++11 的多线程，在Linux环境中，本质是对pthread库的封装！
    std::thread t1(thread_run);

    while (true)
    {
        std::cout << "我是主线程..." << std::endl;
        sleep(1);
    }

    t1.join();

    return 0;
}

// #include <iostream>
// #include <cstdlib>
// #include <string>
// #include <cassert>
// #include <vector>
// #include <pthread.h>
// #include <unistd.h>

// using namespace std;

// // 当成结构体使用
// class ThreadData
// {
// public:
//     int number;
//     pthread_t tid;
//     char namebuffer[64];
// };

// class ThreadReturn
// {
// public:
//     int exit_code;
//     int exit_result;
// };

// //1. start_routine, 现在是被几个线程执行呢？10， 这个函数现在是什么状态？重入状态
// //2. 该函数是可重入函数吗？是的！
// //3. 在函数内定义的变量，都叫做局部变量，具有临时性 -- 今天依旧适用 -- 在多线程情况下， 也没有问题 -- 其实每一个线程都有自己独立的栈结构！
// void *start_routine(void *args)
// {
//     // sleep(1);
//     // 一个线程如果出现了异常，会影响其他线程吗？会的（健壮性或者鲁棒性较差）
//     // 为什么？进程信号，信号是整体发给进程的！

//     ThreadData *td = static_cast<ThreadData *>(args); // 安全的进行强制类型转化
//     int cnt = 10;
//     while (cnt)
//     {
//         cout << "cnt: " << cnt << " &cnt: " << &cnt << endl; // bug
//         cnt--;
//         sleep(1);
//         // return nullptr;
//         // pthread_exit(nullptr);
//         // exit(0); // 能不能用来终止线程，不能，因为exit是终止进程的！，任何一个执行流调用exit都会让整个进程退出
//         // cout << "new thread create success, name: " << td->namebuffer << " cnt: " << cnt-- << endl;
//         // int *p = nullptr;
//         // // p = nullptr;
//         // *p = 0;
//     }

//     // 线程如何终止的问题
//     // delete td;
//     // pthread_exit(nullptr);
//     // return nullptr; // 线程函数结束，return的时候，线程就算终止了

//     // return (void*)td->number; // warning， void *ret = (void*)td->number;
//     // return (void *)106;
//     // pthread_exit((void*)111); // 既然假的地址，整数都能被外部拿到，那么如何返回的是，堆空间的地址呢？对象的地址呢？
//     ThreadReturn * tr = new ThreadReturn();
//     tr->exit_code = 1;
//     tr->exit_result = 106;

//     // ThreadReturn tr; // 在栈上开辟的空间 return &tr;

//     return (void*)100; //右值
// }

// int main()
// {
//     // 1. 我们想创建一批线程
//     vector<ThreadData*> threads;
// #define NUM 10
//     for(int i = 0; i < NUM; i++)
//     {
//         ThreadData *td = new ThreadData();
//         td->number = i+1;
//         snprintf(td->namebuffer, sizeof(td->namebuffer), "%s:%d", "thread", i+1);
//         pthread_create(&td->tid, nullptr, start_routine, td);
//         threads.push_back(td);

//         // pthread_create(&tid, nullptr, start_routine, (void*)"thread one");
//         // pthread_create(&tid, nullptr, start_routine, namebuffer);
//         // sleep(1);
//     }

//     for(auto &iter : threads)
//     {
//         cout << "create thread: " << iter->namebuffer << " : " << iter->tid << " suceesss" << endl;
//     }
//     // 线程是可以被cancel取消的！注意：线程要被取消，前提是这个线程已经跑起来了
//     // 线程如果是被取消的，退出码：-1
//     // PTHREAD_CANCELED;
//     sleep(5);
//     for(int i = 0; i < threads.size()/2; i++)
//     {
//         pthread_cancel(threads[i]->tid);
//         cout << "pthread_cancel : " << threads[i]->namebuffer << " success" << endl;
//     }

//     for(auto &iter : threads)
//     {
//         void *ret = nullptr; // 注意: 是void *哦
//         // ? : 为什么没有见到，线程退出的时候，对应的退出信号？？？ 线程出异常，收到信号，整个进程都会退出！
//         // pthread_join:默认就认为函数会调用成功！不考虑异常问题，异常问题是你进程该考虑的问题！
//         int n = pthread_join(iter->tid, (void**)&ret); // void ** retp; *retp = return (void*)td->number
//         assert(n == 0);
//         cout << "join : " << iter->namebuffer << " success, exit_code: " << (long long)ret << endl;
//         delete iter;
//     }

//     cout << "main thread quit " << endl;

//     // while (true)
//     // {
//     //     cout << "new thread create success, name: main thread" << endl;
//     //     sleep(1);
//     // }

//     // pthread_t id;
//     // pthread_create(&id, nullptr, start_routine, (void *)"thread new");

//     // while (true)
//     // {
//     //     cout << "new thread create success, name: main thread" << endl;
//     //     sleep(1);
//     // }

//     return 0;
// }