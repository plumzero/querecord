
## 参考
[无锁编程基础](https://www.jianshu.com/p/88b5138ec027)
深入理解计算机系统-并发编程

## 锁的种类

可能会遇到很多的锁概念，比如重锁、偏向锁、乐观锁、悲观锁等，这些锁都可以归类为自旋锁、互斥锁或读写锁。
关于这三种锁的联系，在[这里](只有三种锁.md)

## 无锁编程

无锁编程要搞清楚两个问题。1. 为什么要进行无锁编程？2. 如何实现无锁编程？

1. 为什么要进行无锁编程？
    多核心CPU下进行多线程并发编程可以有效提高运行效率，不过多线程之间的上下文切换也会消耗掉一部分时间。
    **进行无锁编程的目的就是尽可能减少线程上下文件之间的切换**，比如原来一段时间内可能会切换五次，无锁编程后只切换两次，这样就提高了效率。

2. 如何实现无锁编程?
    CPU 在执行指令时，会提供一些原子操作，利用这些原子操作，对多线程进行一定的自旋处理，以减少上下文切换。

## 无锁编程的适用性

无锁编程适用于CPU密集性场景。
多个线程均处于忙碌状态时的场景。如果有的线程很忙，有的线程很闲，这个时候就不太适合无锁编程。
无锁编程如果能和线程池结合在一起使用是更好不过的。

## Linux 支持的一些原子操作

[Built-in functions for atomic memory access](https://gcc.gnu.org/onlinedocs/gcc-4.1.0/gcc/Atomic-Builtins.html)

大致有 4 类：

- i++ 型原子操作
  ```c
    type __sync_fetch_and_add (type *ptr, type value, ...)
    type __sync_fetch_and_sub (type *ptr, type value, ...)
    type __sync_fetch_and_or (type *ptr, type value, ...)
    type __sync_fetch_and_and (type *ptr, type value, ...)
    type __sync_fetch_and_xor (type *ptr, type value, ...)
    type __sync_fetch_and_nand (type *ptr, type value, ...)
    ```

- ++i 型原子操作
  ```c
    type __sync_add_and_fetch (type *ptr, type value, ...)
    type __sync_sub_and_fetch (type *ptr, type value, ...)
    type __sync_or_and_fetch (type *ptr, type value, ...)
    type __sync_and_and_fetch (type *ptr, type value, ...)
    type __sync_xor_and_fetch (type *ptr, type value, ...)
    type __sync_nand_and_fetch (type *ptr, type value, ...)
  ```

- 可以利用下面这两个原子操作实现互斥锁
  ```c
    bool __sync_bool_compare_and_swap (type *ptr, type oldval type newval, ...)
    type __sync_val_compare_and_swap (type *ptr, type oldval type newval, ...)
  ```

- 可以利用下面这个原子操作实现自旋锁
  ```c
    type __sync_lock_test_and_set (type *ptr, type value, ...)
  ```
  
## 非锁保护/互斥锁保护/原子操作效率测试

- [测试文件](etest.cpp)

- 测试结果

|  种类/次数 | 第一次 | 第二次 | 第三次 | 第四次 |
|:----:|:-----:|:----:|:------:|:------:|:------:|
| 非锁保护/add0 | 1000016/4028  | 1000019/4217  | 1000010/4520  | 1000016/4178  |
| 互斥锁保护/add1 | 1000019/34261 | 1000019/36318 | 1000019/35147 | 1000019/32999 |
| 原子操作/add2 | 1000019/18653 | 1000019/18029 | 1000019/22747 | 1000019/21267 |

- 结论
	非锁保护下最快，但无法保证数据的同步。互斥锁可以保证数据同步，但效率较慢。原子操作可以保证数据的同步，而且比互斥锁要快(近一倍)。
	
	


