#pragma once

#include <iostream>
#include <queue>
#include <pthread.h>

const int gmaxcap = 500;

template <class T>
class BlockQueue
{   
public:
    BlockQueue(const int &maxcap = gmaxcap):_maxcap(maxcap)
    {
        pthread_mutex_init(&_mutex, nullptr);
        pthread_cond_init(&_pcond, nullptr);
        pthread_cond_init(&_ccond, nullptr);
    }
    void push(const T &in) // 输入型参数，const &
    {
        pthread_mutex_lock(&_mutex);
        // 1. 判断
        // 细节2: 充当条件判断的语法必须是while，不能用if
        while(is_full()) //bug?
        {
            // 细节1：pthread_cond_wait这个函数的第二个参数，必须是我们正在使用的互斥锁！
            // a. pthread_cond_wait: 该函数调用的时候，会以原子性的方式，将锁释放，并将自己挂起
            // b. pthread_cond_wait: 该函数在被唤醒返回的时候，会自动的重新获取你传入的锁
            pthread_cond_wait(&_pcond, &_mutex); //因为生产条件不满足，无法生产，此时我们的生产者进行等待
        }
        // 2. 走到这里一定是没有满
        _q.push(in);
        // 3. 绝对能保证，阻塞队列里面一定有数据
        // 细节3：pthread_cond_signal：这个函数，可以放在临界区内部，也可以放在外部
        pthread_cond_signal(&_ccond); // 这里可以有一定的策略
        pthread_mutex_unlock(&_mutex);
        //pthread_cond_signal(&_ccond); // 这里可以有一定的策略
    }
    void pop(T *out) // 输出型参数：*， // 输入输出型：&
    {
        pthread_mutex_lock(&_mutex);
        //1. 判断
        while(is_empty()) //bug?
        {
            pthread_cond_wait(&_ccond, &_mutex);
        }
        // 2. 走到这里我们能保证，一定不为空
        *out = _q.front();
        _q.pop();

        // 3. 绝对能保证，阻塞队列里面，至少有一个空的位置！
        pthread_cond_signal(&_pcond); // 这里可以有一定的策略
        pthread_mutex_unlock(&_mutex);
    }
    ~BlockQueue()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_pcond);
        pthread_cond_destroy(&_ccond);
    }
private:
    bool is_empty()
    {
        return _q.empty();
    }
    bool is_full()
    {
        return _q.size() == _maxcap;
    }
private:
    std::queue<T> _q;
    int _maxcap; // 队列中元素的上限
    pthread_mutex_t _mutex;
    pthread_cond_t _pcond; // 生产者对应的条件变量
    pthread_cond_t _ccond; // 消费者对应的条件变量
};