#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include <memory>
#include "Thread.hpp"
#include "Mutex.hpp"

// 见见猪跑，下节课详细来谈
// pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// 添加__thread，可以将一个内置类型设置为线程局部存储
// __thread int g_val = 100;
// std::string changeId(const pthread_t &thread_id)
// {
//     char tid[128];
//     snprintf(tid, sizeof(tid), "0x%x", thread_id);
//     return tid;
// }

// void *start_routine(void *args)
// {
//     std::string threadname = static_cast<const char *>(args);
//     // pthread_detach(pthread_self()); //设置自己为分离状态

//     int cnt = 5;
//     while (true)
//     {
//         std::cout << threadname << " running ... : " << changeId(pthread_self()) <<" g_val: "<< g_val << " &g_val: " << &g_val << std::endl;
//         sleep(1);
//         g_val++;
//     }

//     return nullptr;
// }

// 共享资源， 火车票
int tickets = 10000;
// 1. 如何看待锁
//    a. 锁，本身就是一个共享资源！全局的变量是要被保护的，锁是用来保护全局的资源的，锁本身也是全局资源，锁的安全谁来保护呢？
//    b. pthread_mutex_lock、pthread_mutex_unlock:加锁的过程必须是安全的！加锁的过程其实是原子的！
//    c. 如果申请成功，就继续向后执行，如果申请暂时没有成功，执行流会阻塞！
//    d. 谁持有锁，谁进入临界区！
// 2. 如何理解加锁和解锁的本质 --- 加锁的过程是原子的！
// 3. 如果我们想简单的使用，该如何进行封装设计 --- 做一个设计
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// 1. 多个执行流进行安全访问的共享资源 - 临界资源
// 2. 我们把多个执行流中，访问临界资源的代码 -- 临界区 -- 往往是线程代码的很小的一部分
// 3. 想让多个线程串行访问共享资源 -- 互斥
// 4. 对一个资源进行访问的时候，要么不做，要么做完 -- 原子性 ， 不是原子性的情况 -- 一个对资源进行的操作，如果只用一条汇编就能完成 -- 原子性
// 反之：不是原子的 -- 当前理解，方便表述

// 提出解决方案：加锁！

// 就需要尽可能的让多个线程交叉执行
// 多个线程交叉执行本质：就是让调度器尽可能的频繁发生线程调度与切换
// 线程一般在什么时候发生切换呢？时间片到了，来了更高优先级的线程，线程等待的时候。
// 线程是在什么时候检测上面的问题呢？从内核态返回用户态的时候，线程要对调度状态进行检测，如果可以，就直接发生线程切换

class ThreadData
{
public:
    ThreadData(const std::string &threadname, pthread_mutex_t *mutex_p) : threadname_(threadname), mutex_p_(mutex_p)
    {
    }
    ~ThreadData() {}

public:
    std::string threadname_;
    pthread_mutex_t *mutex_p_;
};

void *getTicket(void *args)
{
    // other code
    std::string username = static_cast<const char *>(args);
    // ThreadData *td = static_cast<ThreadData *>(args);
    while (true)
    {
        // 加锁和解锁的过程多个线程串行执行的，程序变慢了！
        // 锁只规定互斥访问，没有规定必须让谁优先执行
        // 锁就是真是的让多个执行流进行竞争的结果
        // pthread_mutex_lock(&lock);
        // pthread_mutex_lock(&lock);
        {
            LockGuard lockguard(&lock); // RAII风格的加锁！
            if (tickets > 0)
            {
                usleep(1254); // 1秒 = 1000毫秒 = 1000 000 微妙 = 10^9纳秒
                // 值得抢
                //  std::cout << td->threadname_ << " 正在进行抢票: "<< tickets << std::endl;
                std::cout << username << " 正在进行抢票: " << tickets << std::endl;
                // 用这段时间来模拟真实的抢票要花费的时间
                tickets--;
                // pthread_mutex_unlock(&lock);
            }
            else
            {
                // pthread_mutex_unlock(&lock);
                break;
            }
        }
        // 抢完票就完了了吗？当然不是
        // usleep(1000); // 形成一个订单给用户
    }

    // other code

    return nullptr;
}

int main()
{
    // #define NUM 4
    //     pthread_mutex_t lock;
    //     pthread_mutex_init(&lock, nullptr);
    //     std::vector<pthread_t> tids(NUM);
    //     for(int i = 0; i < NUM; i++)
    //     {
    //         char buffer[64];
    //         snprintf(buffer, sizeof(buffer), "thread %d", i+1);
    //         ThreadData *td = new ThreadData(buffer, &lock);
    //         pthread_create(&tids[i], nullptr, getTicket, td);
    //     }

    //     for(const auto &tid: tids)
    //     {
    //         pthread_join(tid, nullptr);
    //     }

    pthread_t t1, t2, t3, t4;
    pthread_create(&t1, nullptr, getTicket, (void *)"thread 1");
    pthread_create(&t2, nullptr, getTicket, (void *)"thread 2");
    pthread_create(&t3, nullptr, getTicket, (void *)"thread 3");
    pthread_create(&t4, nullptr, getTicket, (void *)"thread 4");

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    pthread_join(t3, nullptr);
    pthread_join(t4, nullptr);

    // std::unique_ptr<Thread> thread1(new Thread(getTicket, (void *)"user1", 1));
    // std::unique_ptr<Thread> thread2(new Thread(getTicket, (void *)"user2", 2));
    // std::unique_ptr<Thread> thread3(new Thread(getTicket, (void *)"user3", 3));
    // std::unique_ptr<Thread> thread4(new Thread(getTicket, (void *)"user4", 4));

    // thread1->join();
    // thread2->join();
    // thread3->join();
    // thread4->join();
    // Thread t(start_routine);
    // t.start();
    // t.join();
    // // pthread_attr_t;
    // pthread_t tid;
    // pthread_create(&tid, nullptr, start_routine, (void *)"thread 1");
    // std::string main_id = changeId(pthread_self());
    // pthread_detach(tid);

    // std::cout << "main thread running ... new thread id: " << changeId(tid) <<" main thread id: " << main_id << std::endl;

    // // sleep(2);
    // // 一个线程默认是joinable的，如果设置了分离状态，不能够进行等待了！
    // // int n = pthread_join(tid, nullptr);
    // // std::cout << "result: " << n << " : " <<strerror(n) << std::endl;

    // while(true)
    // {
    //     std::cout << "main thread running ... new thread id: " <<\
    //         changeId(tid) <<" main thread id: " << main_id << " g_val: "<< g_val << " &g_val: " << &g_val << std::endl;
    //     sleep(1);
    // }
    return 0;
}