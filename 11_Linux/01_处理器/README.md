
## 设置进程与 CPU 绑定
- 在 Linux 系统中，进程的调度是由内核自动完成的，多核 CPU 结构中，每个核心都有各自的一
  级缓存和二级缓存。如果一个进程在不同的 CPU 核上来回切换执行，各个核心的缓存命中率就会
  受到影响。如果进程不管如何调度，都始终可以在一个核心上执行，那么其数据的的一级缓存和二
  级缓存的命中率就可以显著提高。
- 将进程或线程绑定到特定 CPU 上也称为设置进程或线程与 CPU 的亲和性。
- 在 Linux 系统里，可以使用 CPU_ 系列函数和 sched_setaffinity() 实现进程与 CPU 之间的绑定
  ，具体步骤如下:
    + 定义 _GNU_SOURCE 宏，告诉编译器启用这些函数:
      ```c
        #define _GNU_SOURCE
      ```
    + 声明一个 cpu_set_t ，之后调用  CPU_ZERO() 初始化比特数据:
      ```c
        cpu_set_t mask;
        CPU_ZERO(&mask);
      ```
      cpu_set_t 是一个比特串，每个比特表示进程是否要与某个 CPU 核绑定。
    + 通过  CPU_SET() 来设置 cpu_set_t 中相应的比特位，把进程绑定到对应的 CPU 核心:
      ```c
        CPU_SET(1, &mask);
        CPU_SET(3, &mask);
      ```
      让进程只在核心1和核心5上执行。注意，对 CPU 的编号从 0 开始。
    + 最后通过 sched_setaffinity 完成实际的绑定:
      ```c
        sched_setaffinity(0, sizeof(cpu_set_t), &mask);
      ```
      第一个参数表示要绑定的进程号，为 0 时表示当前进程。

## 亲和性测试
- 注意，要在多 CPU 核心系统上测试。当前测试环境 VM+Ubuntu16.04(4 cores)
- 测试程序，每组测试 5 次:
  ```c
    #include <stdio.h>
    #include <unistd.h>
    #include <sched.h>
    #include "rdtsc.h"

    #define N 1000

    int main()
    {
        cpu_set_t mask;
        
        CPU_ZERO(&mask);
        CPU_SET(0, &mask);
        sched_setaffinity(0, sizeof(cpu_set_t), &mask);
        
        unsigned long long b, e;

        b = rdtsc();
        
        int i;
        int arr[N];
        for (i = 0; i != N; i++) {
            arr[i] = i;
        }
        long sum = 0;
        for (i = 0; i != N; i++) {
            sum += arr[i];
        }

        e = rdtsc();

        printf("%lld\n", e - b);
        
        return 0;
    }
  ```
  未设置亲和性测试结果:
  ```shell
    48748
    176082
    12355
    48759
    47957
  ```
  设置亲和性后测试结果:
  ```shell
    48311
    48623
    49059
    48816
    49486
  ```
  
## 记录
- [精确统计时间](精确统计时间.md)