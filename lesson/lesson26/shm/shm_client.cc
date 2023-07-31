#include "comm.hpp"
#include <unistd.h>

int main()
{
    key_t k = getKey(); 
    printf("key: 0x%x\n", k);
    int shmid = getShm(k);
    printf("shmid: %d\n", shmid);

    char *start = (char*)attachShm(shmid);
    printf("attach success, address start: %p\n", start);

    const char* message = "hello server, 我是另一个进程，正在和你通信";
    pid_t id = getpid();
    int cnt = 1;
    // char buffer[1024];
    while(true)
    {
        sleep(5);
        snprintf(start, MAX_SIZE, "%s[pid:%d][消息编号:%d]", message, id, cnt++);
        // snprintf(buffer, sizeof(buffer), "%s[pid:%d][消息编号:%d]", message, id, cnt++);
        // memcpy(start, buffer, strlen(buffer)+1);
        // pid, count, message
    }

    detachShm(start);

    //done

    return 0;
}



