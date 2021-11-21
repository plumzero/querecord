
## 问题场景
- 守护进程内部创建三个子进程(算上守护进程一共四个进程)，子进程创建完毕后，子进程之间
  会进行线程间通信。通信为子进程一向子进程二不停的发消息，子进程二收到消息后会在其内
  部启动一个可执行程序X进程(启动时长不足1s，但相对较为耗时)，可执行程序启动完毕后，
  向子进程三发送消息。示意如下:
  <h1 align="center">
    <img width="321" height="201" src="../.resource/question-a.jpg" alt="...">
  </h1>
- 三个子进程通过向守护进程发送心跳，如果守护进程超过4s没有接收到来自某个子进程的心跳，
  那么守护进程就会重建该子进程。
- 每个进程各有一个日志记录运行信息。

## 问题描述
- 运行程序后，通过 ps 和 grep 过滤查看进程名，前4s正常，之后突然出现上百条进程。通过
  日志查看是守护进程反复创建子进程二，而原来的子进程二并没有被销毁。
- 查看子进程二日志发现，X进程并没有启动成功，不过后续发现启动不成功不是造成这个问题的
  原因。
- 查看守护进程日志心跳接收信息发现，并没有接收到子进程二发来的心跳信息。可以猜测正是
  因为守护进程对于子进程二的心跳信息过期，导致其重建子进程二。而原来的子进程二实际上
  并没有被销毁，守护进程依然保存其过期心跳信息，所以将会反复创建子进程二，造成子进程
  二数量快速增长。

## 原因分析
- 守护进程反复创建子进程二的原因是没有收到后者的心跳信息，所以猜测应该是在哪里阻塞了。
- 子进程二一共有两条线程，线程一是一个回调线程，负责 epoll 的读写处理，接收来自其他进
  程的信息，或者将本进程用户业务线程内消息发送出去，此外它还负责一个定时回调，内部定义
  了向守护进程发送心跳。
- 线程二是用户业务线程，在该线程内处理来自回调线程的信息，并可以将自己线程产生的消息通
  过回调线程发送出去，实现进程间通信。
- 由于两个线程之间有共同的使用资源，即消息队列，所以定义了互斥锁来实现各个线程对该消息
  队列的独占。两个线程内的锁都是采用 std::unique_lock 实现，具体如下:
  ```c++
    // 回调线程
    std::unique_lock<std::mutex> guard(m_mutex);
    m_messages.push(std::move(msg));
    m_cond.notify_one();
    /** 函数退出后自动释放锁 */
  
    // 用户业务线程
    while (true) {
        std::unique_lock<std::mutex> guard(m_mutex);        // <- 业务线程阻塞在这里
        if (! m_cond.wait_for(guard, std::chrono::seconds(2), [&m_messages](){ return ! m_messages.empty(); })) {
            continue;
        }
        
        std::string msg = std::move(m_messages.front());
        m_messages.pop();
        
        switch(msg type) {
        case xxx:
            start X  ...
        break;
        ...
        }
        /** other deal */
        
        /** 执行完一次 while 后自动释放锁 */
    }
  ```
- 子进程二内没有启动进程X时，所有的进程和线程运行都是正常的，启动X进程时(无论成功与否)，运行
  都会异常。
- 通过添加打印发现用户业务线程阻塞在了 std::unique_lock 构造加锁处，这表示用户业务线程没有办
  法获得这把锁，因为它正在被其他线程，这里是回调线程使用。通过日志发现回调线程没有被阻塞，这
  说明回调线程理论上是可以实现向守护进程发送心跳消息的，但事实上却并没有发送，这是很令人疑惑
  的地方。
- 排查过程中一度对 std::unique_lock 产生了不信任感，不过后来验证自己的想法是错误的。

## 问题原因
- 子进程二内启动X进程耗时相对较长(阻塞启动，虽然耗时不足1s)，且这个过程中子进程依然源源不断地
  向子进程二发送启动X进程的消息。因为互斥锁长时间被用户业务线程所占有(栈内析构销毁，而启动X进
  程要耗费可观时间)，这个时候回调线程的套接字读缓冲区中就会积累大量未读数据，读回调部分程序如
  下:
  ```c++
    char hbuf[NEGOHSIZE];
    ssize_t nh = read(fd, hbuf, NEGOHSIZE);
    if (nh != NEGOHSIZE) {
        return -1;
    }
    
    NegoHeader header;
    memcpy(&header, hbuf, NEGOHSIZE);
    
    size_t bodysize = ntohs(header.bodysize);
    
    char *rbuf = (char *)calloc(1, bodysize);
    if (! rbuf) {
        return -1;
    }
    
    ssize_t nb = read(fd, rbuf, bodysize);
    if (nb != (ssize_t)bodysize) {
        if (rbuf) {
            free(rbuf);
        }
        return -1;
    }
    
    std::string msg(rbuf, nb);
    if (rbuf) {
        free(rbuf);
    }
  ```
  可以看出要读两次(第一次读固定长度协议头，第二次才是具体的消息)，所以从套接字中抽取数据也比较
  费时(但相对启动X进程算是很快的了)。对套接字的读写采用 epoll 反应器机制，程序结构大致如下:
  ```c++
    res = epoll_wait(m_epi, evs, EPOLL_MAX_NUM, 1000);
    for (i = 0; i < res; i++)
    {
        /** prepare it */
        bc->read_bacllback(bc->fd, nullptr, 0, this);
        /** other deal */
        bc->write_bacllback(bc->fd, nullptr, 0, this);
        /** deal tail */
    }
    
    for (bc : clients) {
        bc->timer_callback(bc, this);
    }
  ```
  先进行读写回调，待处理完毕后，再进行后续的定时回调。所有的处理都是串行化执行。看到这里，问题原因
  也已经很明显了，因为用户业务线程长期独占锁，而这时回调线程中积累了大量未处理消息，一旦其获得锁，
  就会阻塞执行 epoll 反应器程序的第一个循环，因为处理消息较多(且子线程一仍然不断向其发送消息)，所以
  没有执行后续的定时回调，守护进程也就无法收到心跳信息。且因为回调线程中的锁无法及时释放(反复使用)，
  导致用户业务线程阻塞在 std::unique_lock 构造加锁处。

## 问题解决
- 用户业务线程执行显示释放锁，即 pop 出一个消息后就释放锁，而不是析构释放锁。如下:
  ```c++
    // 用户业务线程
    while (true) {
        std::unique_lock<std::mutex> guard(m_mutex);        // <- 业务线程阻塞在这里
        if (! m_cond.wait_for(guard, std::chrono::seconds(2), [&m_messages](){ return ! m_messages.empty(); })) {
            continue;
        }
        
        std::string msg = std::move(m_messages.front());
        m_messages.pop();
        guard.unlock();         /** 显式释放锁 */
        
        switch(msg type) {
        case xxx:
            start X  ...
        break;
        ...
        }
        /** other deal */
        
        /** 执行完一次 while 后自动释放锁 */
    }
  ```
- 加上上面一名代码后，程序执行正常，问题基本处理完毕。

## 结尾
- 后续发现 m_messages 还是会积累大量消息，这是子进程一反复发送导致的，实际业务上并不需要如下，改为
  只发送一次。