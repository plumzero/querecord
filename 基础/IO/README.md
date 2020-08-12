
## Linux 下的 I/O
- Linux 下的 I/O 设备主要包括三种: 磁盘，终端，网络。
- Linux 下的 I/O 设备均视为（映射为）文件，应用程序通过各类通用的系统调用，来告知内核对相应文件执行何种操作。
- 所以下面所说的文件操作也可以视为 I/O 操作。

## I/O 基本操作
- 打开文件
  ```c
    #include <sys/stat.h>
    #include <fcntl.h>
    int open(const char *pathname, int flags, .../* mode_t mode */);
  ```  
    + 打开 pathname 所标识的文件，并返回文件描述符，用以在后续函数调用中指代打开的文件。
    + 文件状态标志 flags 可指定文件的打开方式: 只读、只写亦或是读写方式
    + mode 参数指定了由 open() 调用创建文件的访问权限。非创建文件时，可以省略此参数。
    + 文件状态标志 O_CLOEXEC
        + 为新（创建）的文件描述符设置 close-on-exec 标志(FD_CLOEXEC)。
        + 使用 O_CLOEXEC 标志（打开文件），可以免去程序执行 fcntl() 的 F_GETFD 和 F_SETFD 操作来设置 close-on-exec 标志的额外工作。
        + 在多线程程序中执行 fcntl() 的 F_GETFD 和 F_SETFD 操作有可能导致竞争状态，而使用 O_CLOEXEC 标志则能够避免这一点。

- 改变当前的文件位置
  ```c
    #include <unistd.h>
    off_t lseek(int fd, off_t offset, int whence);
  ```
    + 针对 fd 所指代的已打开文件，lseek() 系统调用依照 offset 和 whence 参数值调整该文件的偏移量。失败时返回 -1。
    + offset 参数: 可以为正数也可以为负数。
    + whence 参数取值:
        + SEEK_SET   将文件偏移量设置为从文件头部起始点开始的 offset 个字节。
        + SEEK_CUR   相对于当前文件偏移量，将文件偏移量调整 offset 个字节。
        + SEEK_END   将文件偏移量设置为起始于文件尾部的 offset 个字节。
    + 注意：lseek() 并不适用于所有类型的文件。不允许将 lseek() 应用于管道、FIFO、socket 或者终端。

- 读写文件
  ```c
    #include <unistd.h>
    ssize_t read(int fd, void *buffer, size_t count);
  ```
    + 从 fd 所指代的打开文件中读取至多 count 字节的数据，并存储到 buffer 中。
    + 返回值为实际读取的字节数，如果无字节可读（如读取文件结束符 EOF 时），则返回 0。出错返回 -1。
  ```c
    #include <unistd.h>
    ssize_t write(int fd, void *buffer, size_t count);
  ```
    + 从 buffer 中读取多达 count 字节的数据写入到由 fd 所指代的已打开文件中。
    + 返回值为实际写入文件中的字节数，且有可能小于 count。
    + 注意：对磁盘文件执行 I/O 操作时， write() 调用成功并不能保证数据已经写入磁盘。因为为了减少磁盘活动量和加快 write() 系统调用，内核会缓存磁盘的 I/O 操作。

- 文件控制
  ```c
    #include <sys/ioctl.h>
    int ioctl(int fd, int request, ... /* argp */);
  ```
    + 通过 request 参数指定将在 fd 上执行的控制操作。具体设备的头文件定义了可传递给 request 参数的常量。
    + ioctl() 根据 request 的参数值来确定 argp 所期望的类型。通常，argp 是指向整数或结构的指针。

- 关闭文件
  ```c
    #include <unistd.h>
    int close(int fd);
  ```
  + 释放文件描述符 fd 以及与之相关的内核资源。
  
## 读取文件元数据
- 只能通过底层 Linux/Unix I/O 操作为读取元数据。
- 常见的操作函数有 `stat` 和 `fstat` 。
  ```c
    #include <unistd.h>
    #include <sys/stat.h>
    
    int stat(const char *filename, struct stat* buf);
    int fstat(int fd, struct stat* buf);
  ```
  
## 文件共享
- 内核用三个相关的数据结构来表示打开的文件，分别是:
    + 文件描述符: 可以看作是共享智能指针
    + 文件表: 可以看作是共享指针指向的真正对象，它也有引用计数，表示为多个文件描述符所引用。
    + v-node表: 保存每个真正对象的元信息。
- 在同一个进程内，多个描述符引用同一个文件，那么多个描述符可以从不同的位置对这个文件进行读。但如果其中一个描述符对文件作出改写操作，那么其他描述符也会观察到。
- 父进程 fork 子进程后，子进程获得父进程描述符表的一个副本。父子进程共享相同的打开文件表集合(文件表没有生成副本)，因此共享相同的文件位置。

## I/O 重定向原理
- 通过 dup2 函数实现
  ```c
    #include <unistd.h>
    int dup2(int oldfd, int newfd);
  ```
    + dup2 会拷贝描述符表表项 oldfd 到描述符表表项 newfd, 而 newfd 以前的内容会被覆盖。如果 newfd 已经打开了，dup2 会在拷贝 oldfd 之前关闭 newfd。
    + 简单说就是 newfd 所指向的文件表的引用计数减1，而 oldfd 所指向的文件表的引用计数加1。
    
## 以上说的都是底层的 Linux/Unix 系统 I/O，现在来看标准 I/O

## 标准 I/O
- 标准 I/O 将一个打开的文件模型化为一个流。
- 系统I/O围绕文件描述符操作，标准I/O围绕文件指针 FILE 操作。



