
进程间彼此不能直接通信。进程本身无法创建出新进程，哪怕是"自行了断"都不行。进程也不能与计算机外接的输入或输出设备直接通信。

进程间的所有通信都要通过内核提供的通信机制来完成。响应进程发出的请求，内核会创建新的进程，终结现有进程。最后，由内核(特别是设备驱动程序)来执行与输入/输出设备之间的所有直接通信，按需与用户进程交互信息。

Linux 进程间通信(IPC)机制:

1. 信号(signal)，用来表示事件的发生
2. 管道和 FIFO，用于在进程间传递数据
3. 套接字
4. 文件锁定
5. 消息队列，用于在进程间交换消息(数据包)
6. 信号量(semaphore)，用来同步进程动作
7. 共享内存，允许两个及两个以上进程共享一块内存
