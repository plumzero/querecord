
## CPU 的缓存分级
- 至少有一级缓存和二级缓存，高端的 cpu 还会有三级缓存；
- 多核 CPU 结构中，每个核心有各自的一级缓存和二级缓存，三级缓存是共用的。
- 一级缓存又分为数据缓存(Data Cache, D-Cache)和指令缓存(Instruction Cache, I-Cache)，
  分别用来存放数据和执行这些数据的指令。数据缓存和指令缓存可以同时被 CPU 访问，减少
  了争用 Cache 所造成的冲突，提高了处理器效能。
  
## 各级缓存的差别
- 用于存储数据的缓存部分通常被称为 RAM。RAM 又分为两种，静态 RAM(SRAM)和动态 RAM(DRAM)
  。
- SRAM 存储速度比 DRAM 快，但 SRAM 集成度低(存储相同的数据，SRAM 体积是 DRAM 的6倍)，价
  格也相对较昂贵。
- CPU 的一级缓存通常都是 SRAM。二级缓存采用高速 DRAM(高速 DRAM 速度要比常规 DRAM 快，但
  比 SRAM 慢)。三级缓存的 DRAM 比二级缓存慢，但比内存快。
- 缓存中的内容都是内存中访问频率高的数据的拷贝(映射)，它们的存在都是为了减少高速的 CPU
  对慢速内存的访问。一级缓存、二级缓存、三级缓存的容量依次递增。

## Linux 下查看 CPU 高速缓存信息(VM+Ubuntu)
- 查看 CPU 的数量
  ```shell
    # ls /sys/devices/system/cpu
    cpu0  cpu2  cpufreq  isolated    modalias  online    power    smt     vulnerabilities
    cpu1  cpu3  cpuidle  kernel_max  offline   possible  present  uevent
  ```
  当前系统有四颗 CPU 。
- 查看 CPU 缓存(以第一颗 CPU(cpu0) 为例)
  ```shell
    # ls /sys/devices/system/cpu/cpu0/cache/
    index0  index1  index2  index3  power  uevent
  ```
  当前系统缓存一共有三级，其中 index0 和 index1 是一级缓存(分别代表 D-Cache 和 I-Cache)，
  index2 是二级缓存，index3 是三级缓存。
- 查看一级缓存 D-Cache 缓存的信息
  ```shell
    # cat /sys/devices/system/cpu/cpu0/cache/index0/level
    1
    # cat /sys/devices/system/cpu/cpu0/cache/index0/type
    Data
    # cat /sys/devices/system/cpu/cpu0/cache/index0/size
    32K
  ```
  index0 缓存是一级缓存，类型是 D-Cache, 容量是 32K 。
- 查看一级缓存 I-Cache 缓存的信息
  ```shell
    # cat /sys/devices/system/cpu/cpu0/cache/index1/level
    1
    # cat /sys/devices/system/cpu/cpu0/cache/index1/type
    Instruction
    # cat /sys/devices/system/cpu/cpu0/cache/index1/size
    32K
  ```
  index1 缓存是一级缓存，类型是 I-Cache, 容量是 32K 。
- 查看二级缓存的信息
  ```shell
    # cat /sys/devices/system/cpu/cpu0/cache/index2/level
    2
    # cat /sys/devices/system/cpu/cpu0/cache/index2/type
    Unified
    # cat /sys/devices/system/cpu/cpu0/cache/index2/size
    256K
  ```
- 查看三级缓存的信息
  ```shell
    # cat /sys/devices/system/cpu/cpu0/cache/index3/level
    3
    # cat /sys/devices/system/cpu/cpu0/cache/index3/type
    Unified
    # cat /sys/devices/system/cpu/cpu0/cache/index3/size
    6144K
  ```

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