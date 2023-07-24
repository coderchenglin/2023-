#include <iostream>
#include <unistd.h>
#include <cassert>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <cstdio>

using namespace std;


//父进程读,子进程写
int main()
{
    int fds[2];
    int ret = pipe(fds);
    assert(ret == 0);

    //[0] : 读取
    //[1] : 写入
    cout << "fds[0]: " << fds[0] << endl;  //3
    cout << "fds[0]: " << fds[1] << endl;  //4

    //第二步 ; fork
    pid_t id = fork();
    assert(id  >= 0);
    if(id == 0)
    {
        //子进程写入
        close(fds[0]);
        //子进程通信代码
        //string msg = "hello I'm child";
        const char* s = "我是子进程,我正在给你发消息";
        int cnt = 0;
        while(true)
        {
            cnt++;
            char buffer[1024];  //只有子进程能看到
            snprintf(buffer,sizeof buffer, "child->parent say: %s[%d] pid : [%d]\n",s,cnt,getpid());
            write(fds[1],buffer,strlen(buffer)); //不用+1 有效字段写进去就行
            cout << "count: "<< cnt <<endl;
            //sleep(1);  //细节,每隔1s写一次
        }


        exit(0);
    }

    //父进程进行读取
    close(fds[1]);
    //父进程通信代码
    while(true)
    {
        sleep(5);
        char buffer[1024];
        //如果管道中没有了数据, 读端再读,默认会直接阻塞当前正在读取的进程
        cout << "AAAAAAAAAAAAAAAAAAAA" << endl;
        ssize_t s = read(fds[0],buffer,sizeof(buffer) - 1);
        cout << "BBBBBBBBBBBBBBBBBBBB" << endl;
        if(s > 0)
            buffer[s] = 0;
        cout << "Get message#" << buffer << "| my pid: " << getpid() <<endl;

        //sleep(5);
    } 

    ret = waitpid(id,nullptr,0);
    assert(ret == id);

    return 0;
}