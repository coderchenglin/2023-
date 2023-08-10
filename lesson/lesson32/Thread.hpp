#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include <functional>
#include  <pthread.h>
// header only 开源代码

class Thread;

//上下文,当成一个大号的结构体
class Context
{
public:
    Thread *this_;
    void *args_;
public:
    Context():this_(nullptr), args_(nullptr)
    {}
    ~Context()
    {}
};

class Thread
{
public:
    // using func_t = std::function<void*(void*)>;
    typedef std::function<void*(void*)> func_t;
    const int num = 1024;
public:
    Thread(func_t func, void *args = nullptr, int number = 0): func_(func), args_(args)
    {
        // name_ = "thread-";
        // name_ += std::to_string(number);

        char buffer[num];
        snprintf(buffer, sizeof buffer, "thread-%d", number);
        name_ = buffer;

         // 异常 == if: 意料之外用异常或者if判断
        // assert: 意料之中用assert
        Context *ctx = new Context();
        ctx->this_ = this;
        ctx->args_ = args_;
        int n = pthread_create(&tid_, nullptr, start_routine, ctx); //TODO
        assert(n == 0); //编译debug的方式发布的时候存在，release方式发布，assert就不存在了，n就是一个定义了，但是没有被使用的变量
        // 在有些编译器下会有warning
        (void)n;
    }
    // 在类内创建线程，想让线程执行对应的方法，需要将方法设置成为static
    static void *start_routine(void *args) //类内成员，有缺省参数！
    {
        Context *ctx = static_cast<Context *>(args);
        void *ret = ctx->this_->run(ctx->args_);
        delete ctx;
        return ret;
        // 静态方法不能调用成员方法或者成员变量
    }

    void join()
    {
        int n = pthread_join(tid_, nullptr);
        assert(n == 0);
        (void)n;
    }

    void *run(void *args)
    {
        return func_(args);
    }

    ~Thread()
    {
        //do nothing
    }
private:
    std::string name_;
    func_t func_;
    void *args_;

    pthread_t tid_;
};