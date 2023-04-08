#include <stdio.h>
#include <signal.h>

void handler(int signum)
{
    printf("Received signal %d.\n", signum);
}

int main()
{
    // 设置 SIGINT 信号的处理函数为 handler
    if (signal(SIGINT, handler) == SIG_ERR) {
        perror("signal");
        return 1;
    }

    // 进程运行中，等待接收信号
    while (1) {
        // do something
    }

    return 0;
}

