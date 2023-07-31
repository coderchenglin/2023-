#ifndef _COMM_HPP_
#define _COMM_HPP_

#include <iostream>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sys/ipc.h>
#include <sys/shm.h>

#define PATHNAME "."
#define PROJ_ID  0x66

#define MAX_SIZE 4097  // --- 内核给你的会向上取整， 内核给你的，和你能用的，是两码事


key_t getKey()
{
    key_t k = ftok(PATHNAME, PROJ_ID); //可以获取同样的一个Key！
    if(k < 0)
    {
        // cin, cout, cerr -> stdin, stdout, stderr -> 0, 1, 2
        std::cerr << errno << ":" << strerror(errno) << std::endl;
        exit(1);
    }
    return k;
}

int getShmHelper(key_t k, int flags)
{
    // k是要shmget，设置进入共享内存属性中的！用来表示
    // 该共享内存，在内核中的唯一性！！
    // shmid vs key:
    // fd    vs inode
    int shmid = shmget(k, MAX_SIZE, flags);
    if(shmid < 0)
    {
        std::cerr << errno << ":" << strerror(errno) << std::endl;
        exit(2);
    }
    return shmid;
}

int getShm(key_t k)
{
    return getShmHelper(k, IPC_CREAT);
}

int createShm(key_t k)
{
    return getShmHelper(k, IPC_CREAT | IPC_EXCL | 0600);
}

void *attachShm(int shmid)
{
    // int a = 10;
    // 100u; // 字面值
    // 纯数字是没有意义的，必须得有类型才可以
    // 10u;
    // 10L;
    // 10;
    // 3.14f;
    // 100元，200$
    void *mem = shmat(shmid, nullptr, 0); //64系统，8
    if((long long)mem == -1L)
    {
        std::cerr <<"shmat: "<< errno << ":" << strerror(errno) << std::endl;
        exit(3);
    }
    return mem;
}

void detachShm(void *start)
{
    if(shmdt(start) == -1)
    {
        std::cerr <<"shmdt: "<< errno << ":" << strerror(errno) << std::endl;
    }
}

void delShm(int shmid)
{
    if(shmctl(shmid, IPC_RMID, nullptr) == -1)
    {
        std::cerr << errno << " : " << strerror(errno) << std::endl;
    }
}

#endif








