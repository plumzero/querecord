
## 内存问题一览
1 级: 致命错误。
2 级: 危险错误。
3 级: 警告信息。
4 级: 提示信息(非错误)。

| 内存信息 | 描述 | 错误等级 |
|:--------:|:----:|:--------:|
| ABR      | Array Bounds Read 数组越界读 | 3 |
| ABW      | Array Bounds Write 数组越界写 | 2 |
| BSR      | Beyond Stack Read 越栈读 | 3 |
| BSW      | Beyond Stack Write 越栈写 | 3 |
| COR      | Core Dump Imminent 非法操作 | 1 |
| FIU      | File Descriptors In Use 文件描述符被使用 | 4 |
| FMM      | Freeing Mismatched Memory 释放错误内存 | 2 |
| FMR      | Free Memory Read 对已释放内存读 | 3 |
| FMW      | Free Memory Write 对已释放内存写 | 2 |
| FNH      | Freeing Non Heap Memory 释放非堆内存 | 2 |
| FUM      | Freeing Unallocated Memory 释放了没有分配的内存 | 2 |
| IPR      | Invalid Pointer Read 非法指针读 | 1 |
| IPW      | Invalid Pointer Write 非法指针写 | 1 |
| MAF      | Malloc Failure 分配内存失败 | 4 |
| MIU      | Memory In-Use 内存正在使用 | 4 |
| MLK      | Memory Leak 内存泄露 | 3 |
| MRE      | Malloc Reentrancy Error remalloc错 | 2 |
| MSE      | Memory Segment Error 内存段错 | 3 |    
| NPR      | Null Pointer Read 空指针读 | 1 |
| NPW      | Null Pointer Write 空指针写 | 1 |
| PAR      | Bad Parameter 错误的参数 | 3 |
| PLK      | Potential Leak 潜在的内存泄露 | 3 |
| SBR      | Stack Array Bounds Read 栈数组越界读 | 3 |
| SBW      | Stack Array Bounds Write 栈数级越界写 | 2 |
| SIG      | Signal 信号 | 4 |    
| SOF      | Stack Overflow 栈溢出 | 3 |
| UMC      | Uninitialized Memory Copy 对未初始化的内存进行拷贝 | 3 |
| UMR      | Uninitialized Memory Read 对未初始化的内存读 | 3 |
| WPF      | Watchpoint Free 释放被监控的内存 | 4 |
| WPM      | Watchpoint Malloc 被监控的内存分配 | 4 |
| WPN      | Watchpoint Entry 被监控的内存 | 4 |
| WPR      | Watchpoint Read 被监控的内存读 | 4 |
| WPW      | Watchpoint Write 被监控的内存写 | 4 |
| WPX      | Watchpoint Exit 退出被监控的内存 | 4 |
| ZPR      | Zero Page Read 零页面读 | 1 |
| ZPW      | Zero Page Write 零页面写 | 1 |

## 常用到的命令
- 跟踪所有形式的内存泄漏
  ```shell
    valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./test
    valgrind --tool=memcheck  --leak-check=full --vex-guest-max-insns=25 --show-leak-kinds=all -v --log-file="memcheck.txt"
  ```
- 为log信息添加时间戳并输出到文件
  ```shell
    valgrind --time-stamp=yes --log-file=check.log ./test
  ```
- 指定log信息跨进程传输(很好很强大，不过对端接收端需要自己写一个接收程序，监听端口号必须在
  1024 - 65535之间)
  ```shell
    valgrind --leak-check=full --log-socket=192.168.10.137:7777
  ```
  可以不加端口号，此时默认发送对端进程监听端口号1500
- 检测未初始化值
  ```shell
    valgrind --track-origins=yes ./test
  ```

## valgrind 五种内存泄漏场景及调试命令
```shell
    LEAK SUMMARY:
        definitely lost: 0 bytes in 0 blocks
        indirectly lost: 0 bytes in 0 blocks
          possibly lost: 0 bytes in 0 blocks
        still reachable: 568 bytes in 1 blocks
             suppressed: 0 bytes in 0 blocks
```
- definitely lost
    + 场景: malloc分配之后未free释放掉。
    + 命令:
      ```shell
        valgrind --tool=memcheck --leak-check=full ./test
      ```
- indirectly lost
    + 场景: 使用 libcurl 库接口调用时出现过，不用太过关注
- possibly lost
    + 暂时没发现
- still reachable：
    + 场景: fopen 打开文件之后未调用 fclose 关闭掉与该文件关联的流缓冲区，此缓冲区由系统分配。
    + 解释:
        + fopen 打开一个文件后，系统会为该文件关联一个流缓冲区。用户对文件进行读时，系统会
          预先将磁盘内文件内容读取到流缓冲区内，这样用户读取文件实际上是读取流缓冲。用户对
          文件进行写时，系统会预先将用户内容写到流缓冲区内，之后再写到磁盘文件内。这可以有
          效减少用户对磁盘的频繁访问，提高读写速度。
        + 如果使用 open 打开一个文件，之后未调用 close 关闭，则不会出现这种类型的内存错误。
          因为 open并不会为文件关联一个缓冲区。
    + 命令:
      ```shell
        valgrind --track-fds=yes -v ./test          ## 跟踪描述符是否关闭
        valgrind --tool=memcheck --show-reachable=yes -v ./test ##查看 still reachable 形式的内存泄漏(useless)
      ```
- 附 Memcheck 检测提示含义英文版
  ```shell
    1. "definitely lost" means your program is leaking memory -- fix those leaks!
    2. "indirectly lost" means your program is leaking memory in a pointer-based structure. (E.g. if the root node of a binary tree is "definitely lost", all the children 
       will be "indirectly lost".) If you fix the "definitely lost" leaks, the "indirectly lost" leaks should go away.
    3. "possibly lost" means your program is leaking memory, unless you're doing unusual things with pointers that could cause them to point into the middle of an allocated 
       block; see the user manual for some possible causes. Use --show-possibly-lost=no if you don't want to see these reports.
    4. "still reachable" means your program is probably ok -- it didn't free some memory it could have. This is quite common and often reasonable. Don't use --show-reachable=yes 
       if you don't want to see these reports.
    5. "suppressed" means that a leak error has been suppressed. There are some suppressions in the default suppression files. You can ignore suppressed errors.
  ```