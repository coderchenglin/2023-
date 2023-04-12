#include <stdio.h>
#include <pthread.h>

void* say_hello(void* args)
{
    printf("Hello, world!\n");
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, say_hello, NULL);
    pthread_join(tid, NULL);
    printf("Thread finished!\n");
    return 0;
}

