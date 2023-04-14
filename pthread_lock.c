#include <pthread.h>

pthread_rwlock_t rwlock; // 定义一个读写锁

int main() {
    // 初始化读写锁
    pthread_rwlock_init(&rwlock, NULL);

    // 在读模式下使用锁
    pthread_rwlock_rdlock(&rwlock);

    // 读取数据
    // ...

    // 释放读模式下的锁
    pthread_rwlock_unlock(&rwlock);

    // 在写模式下使用锁
    pthread_rwlock_wrlock(&rwlock);

    // 写入数据
    // ...

    // 释放写模式下的锁
    pthread_rwlock_unlock(&rwlock);

    // 销毁读写锁
    pthread_rwlock_destroy(&rwlock);

    return 0;
}

