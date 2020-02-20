
## 参考
- [pthread_rwlock_init 和 pthread_rwlock_destroy 函数调用失败的可能原因及处理](https://linux.die.net/man/3/pthread_rwlock_init  Errors)

## 主要函数调用
- int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock, const pthread_rwlockattr_t *restrict attr);
    + 作用: 初始化读写锁 rwlock ，attr 是 NULL 时使用缺省属性，此时状态为未锁定态；
    + 初始化后，读写锁可以一直被使用；
    + 对已初始化的读写锁再进行初始化，其后果是未定义的；
    + 直接使用未初始化的读写锁，其后果是未定义的；    
- int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
    + 作用: 释放读写锁 rwlock；
    + 调用此函数后，rwlock 会被设置为无效值，由此（对其他拥有该锁的线程）造成的后果是未定义的；
    + 试图销毁一个未初始化的读写锁的结果也是未定义的；
    
## 使用事项
- 读写锁不适合多线程时日志的写入，因为日志很少有读出的，使用普通锁即可。
- 读写锁适合于对数据结构读的次数远大于写的情况，比如证书的轮询更新，数据库操作读次数多于写的情
  况。

