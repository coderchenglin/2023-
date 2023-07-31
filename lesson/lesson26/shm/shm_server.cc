#include "comm.hpp"
#include <unistd.h>

int main()
{
    key_t k = getKey(); 
    printf("key: 0x%x\n", k); // key
    int shmid = createShm(k);
    printf("shmid: %d\n", shmid); //shmid 

    // sleep(5);
    
    char *start = (char*)attachShm(shmid);
    printf("attach success, address start: %p\n", start);

    // 使用
    while(true)
    {
        // char buffer[]; read(pipefd, buffer, ...)
        printf("client say : %s\n", start);
        struct shmid_ds ds;
        shmctl(shmid, IPC_STAT, &ds);
        printf("获取属性: size: %d, pid: %d, myself: %d, key: 0x%x",\
                ds.shm_segsz, ds.shm_cpid, getpid(), ds.shm_perm.__key);
        sleep(1);
    }

    // 去关联
    detachShm(start);

    sleep(10);

    // 删除共享内存
    delShm(shmid);
    return 0;
}
