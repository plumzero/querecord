
进程可以通过增加堆的大小来分配内存，所谓堆是一段长度可变的连续虚拟内存，始于进程的未初始化数据段末尾，随着内存的分配和释放而增减。通常将堆的当前内存边界称为"program break"。

最开始时，program break 正好位于未初始化数据段末尾之后。在 program break 的位置抬升后，程序可以访问新分配区域内的任何内存地址，而此时物理内存页尚未分配。内核会在进程首次试图访问这些虚拟内存地址时自动分配新的物理内存页。

Linux/Unix 提供了两个操纵 program break 的系统调用: brk() 和 sbrk() 。
```c
    #include <unistd.h>

    int brk(void *end_data_segment);
                Returns 0 on success, or -1 on error
    void *sbrk(intptr_t increment);
                Returns previous program break on success, or (void*)-1 on error
```
* 系统调用 brk() 会将 program break 设置为参数 end_data_segment 所指定的位置。由于虚拟内存以页为单位进行分配，end_data_segment 实际会四舍五入到下一个内存页的边界处(实际测试的结果并没有进行四舍五入，而是按实际的数值进行抬升)。当试图将 program break 设置为个低于其初始值的位置时，有可能会导致无法预知的行为。
* 调用 sbrk() 将 program break 在原有地址上增加参数 increment 指定的大小。用于声明 increment 的 intptr_t 类型属于整数数据类型。若调用成功，sbrk() 返回前一个 program break 的地址。换言之,如果 program break 增加，那么返回值是指向这块新分配内存起始位置的指针。
* 调用 sbrk(0) 将返回 program break 的当前位置，对其不做改变。在意图跟踪堆的大小，或是监视内存分配函数包的行为时，可能会用到这一用法。

[测试程序](01_brk_sbrk.c)
