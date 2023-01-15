
> 关于 buffers 和 cache
> 二者都是由操作系统为提高 I/O 性能而分配管理的，buffers 是将被写入到磁盘的缓冲区的数据，cache 是从磁盘读出到缓存的数据。

除了 top 和 free 外，其他命令都在 sysstat 包中。

Debian 系列安装:
```sh
    apt-get install sysstat
```

RedHat 系列安装:
```sh
    yum instal sysstat
```


### top

top 可以实时监控系统状态，输出系统整体资源占用状况以及各个进程的资源占用状况。

top 命令的输出被一行空行分为两部分，空行以上的信息为服务器状态的整体统计信息，空行以下部分为各个进程的状态信息。

上部分内容:
```sh
    top - 09:03:36 up  1:24,  4 users,  load average: 0.02, 0.04, 0.05
    Tasks: 112 total,   1 running, 111 sleeping,   0 stopped,   0 zombie
    %Cpu(s):  0.0 us,  0.1 sy,  0.0 ni, 99.8 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
    KiB Mem:   1010656 total,   412872 used,   597784 free,    25040 buffers
    KiB Swap:   901116 total,        0 used,   901116 free.   179368 cached Mem
```
其内容说明如下:
```sh
    top - 当前时间 09:03:36 系统已运行1小时24分没有重启，当前有4个用户登录操作系统，最近1分钟、5分钟、15分钟的系统负载分别是:0.02、0.04、0.05
    任务运行情况：当前共112个进程，1个正在运行，111个在睡眠，0个进程停止，0个僵尸进程
    CPU:用户CPU占用0.0%，内核CPU占用0.1%，特定优先级的进程CPU占用0.0%，空闲CPU为99.8%，因为IO等待的CPU占用0.0%，硬中断CPU占用0.0%，软中断CPU占用0.0%，虚拟机盗取占用0.0%
    内存:共有1010656，已使用412872，可用597784，buffers使用了25040
    虚拟内存:共有901116，已使用0，可用901116，cache使用了179368
```

下部分内容:
```sh
   PID USER      PR  NI    VIRT    RES    SHR S  %CPU %MEM     TIME+ COMMAND
     1 root      20   0   28600   4688   3072 S   0.0  0.5   0:01.41 systemd                                                                                                
     2 root      20   0       0      0      0 S   0.0  0.0   0:00.00 kthreadd
     3 root      20   0       0      0      0 S   0.0  0.0   0:02.17 ksoftirqd/0
     5 root       0 -20       0      0      0 S   0.0  0.0   0:00.00 kworker/0:0H
     6 root      20   0       0      0      0 S   0.0  0.0   0:00.14 kworker/u256:0
     7 root      20   0       0      0      0 S   0.0  0.0   0:03.72 rcu_sched
     8 root      20   0       0      0      0 S   0.0  0.0   0:00.00 rcu_bh
```
各个进程的状态信息区域的输出值所代表的含义是:
* PID: 进程id
* USER: 进程所有者
* PR: 进程所有者
* NI: 进程优先级的修正值
* VIRT: 进程使用的虚拟内存总量
* RES: 进程使用的物理内存大小(单位 KB)
* SHR: 共享内存大小
* S: 进程状态。D=不可中断的睡眠状态 R=运行 S=睡眠 T=跟踪/停止 Z=僵尸进程
* %CPU: 上次更新到现在的CPU时间占用百分比
* %MEM: 进程使用的物理内存百分比
* TIME+: 进程使用的CPU时间总计，单位 1/100 秒
* COMMAND: 进程运行的命令名

### free

free 命令显示当前系统的内存使用情况。

```sh
    root@debian:~# free -m
                total       used       free     shared    buffers     cached
    Mem:           986        408        578         17         25        178
    -/+ buffers/cache:        205        781
    Swap:          879          0        879
```
其内容说明如下:
```sh
    Mem: 当前机器内存共有986MB，已使用408MB，可用578MB，其中total=used+free。共享内存为17MB，buffers使用了25MB。
    -/+ buffers/cache: 前一个值是 used - buffers/cached 的值，是应用程序真正使用的内存，这里是205MB；后一个是 free + buffers/cache 的值，表示理论上可以被使用的内存，这里是781MB。
    Swap: 总的虚拟内存和可用的虚拟内存。
```

free 常用于数据库服务器的观察。数据库在运行期间，会一直频繁地存取数据，对于操作系统而言也是频繁地存取数据，对于操作系统而言也是频繁地存取数据。经过一段时间的运行，可能发现 free 命令的输出结果中，可用内存越来越少，通常都是因为缓存。这是由于 Linux 为了提升 I/O 性能和减少磁盘压力，使用了 buffer cache 和 page cache，buffer cache 针对磁盘的写进行缓存，直接对磁盘进行操作的数据会缓存到 buffer cache，而文件系统中的数据则是交给 page cache 进行缓存，即使数据库任务进行结束，cache 也不会被主动释放。所以，是否使用到 Swap 可以作用判断内存是否够用的一个简单标准，只要没有使用到 Swap，就说明内存还够用，在数据库需要内存时，cache 可以很快被回收。

如果想把缓存释放出来，可以使用如下命令:
```sh
    root# sync
    root# echo 1 > /proc/sys/vm/drop_caches
```
需要注意，在生产环境释放缓存的命令要慎用，避免引起性能波动。

### vmstat

vmstat 是 Linux 中的虚拟内存统计工具，用于监控操作系统的虚拟内存、进程、CPU等的整体情况。

vmstat 最常规的用法是: `vmstat delay count`，即每隔 delay 秒采样一次，共采样 count 次。如果省略 count，则一直按照 delay 时间进行采样，直到用户手动中断停止为止。

```sh
    root@debian:~# vmstat 3 5
    procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
    r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
    1  0      0 590544  26196 182432    0    0     6     1   16   26  0  0 100  0  0
    0  0      0 590536  26196 182448    0    0     0     0   44   70  0  0 100  0  0
    0  0      0 590536  26204 182440    0    0     0     4   40   65  0  0 100  0  0
    0  0      0 590536  26204 182448    0    0     0     0   40   59  0  0 100  0  0
    0  0      0 590784  26204 182448    0    0     0     0   50   76  0  0 100  0  0
```
vmstat 的输出第一行显示了系统自启动以来的平均值，从第二行开始显示现在正在发生的情况。每一列的含义如下:
* r: 当前 CPU 队列中有几个进程在等待，持续为 1 说明有进程一直在等待，超过核心数说明压力过大
* b: 当前有多少个进程进入不可中断式睡眠状态
* swpd: 已经使用的交换分区的大小
* free: 当前的空闲内存
* buff: 已经使用的 buffer 的大小，特指 buffer cache(存在用来描述文件元数据的cache)
* cache: 已经使用的 page cache 的大小，特指文件的 page 的 cache
* si/so: 从磁盘交换到 Swap 分区和从 Swap 分区交换到磁盘的大小
* in: 每秒被中断的进程数
* cs: 每秒多少个 CPU 进程在进进出出

### iostat

iostat 命令用于整个系统、适配器、tty设备、磁盘和CD-ROM的输入/输出统计信息，但最常用的是用 iostat 来监控磁盘的输入输出，其用法与 vmstat 相同。
```sh
    root@debian:~# iostat -dx /dev/sda1 3 5
    Linux 3.16.0-4-amd64 (debian)   09/26/2021      _x86_64_        (4 CPU)

    Device:         rrqm/s   wrqm/s     r/s     w/s    rkB/s    wkB/s avgrq-sz avgqu-sz   await r_await w_await  svctm  %util
    sda1              0.15     0.87    1.65    0.55    29.43    10.28    36.11     0.00    2.25    1.48    4.56   0.71   0.16

    Device:         rrqm/s   wrqm/s     r/s     w/s    rkB/s    wkB/s avgrq-sz avgqu-sz   await r_await w_await  svctm  %util
    sda1              0.00     0.00    0.00    0.00     0.00     0.00     0.00     0.00    0.00    0.00    0.00   0.00   0.00

    Device:         rrqm/s   wrqm/s     r/s     w/s    rkB/s    wkB/s avgrq-sz avgqu-sz   await r_await w_await  svctm  %util
    sda1              0.00     0.66    0.00    0.66     0.00     5.32    16.00     0.00    2.00    0.00    2.00   2.00   0.13

    Device:         rrqm/s   wrqm/s     r/s     w/s    rkB/s    wkB/s avgrq-sz avgqu-sz   await r_await w_await  svctm  %util
    sda1              0.00     0.00    0.00    0.00     0.00     0.00     0.00     0.00    0.00    0.00    0.00   0.00   0.00

    Device:         rrqm/s   wrqm/s     r/s     w/s    rkB/s    wkB/s avgrq-sz avgqu-sz   await r_await w_await  svctm  %util
    sda1              0.00     0.00    0.00    0.00     0.00     0.00     0.00     0.00    0.00    0.00    0.00   0.00   0.00
```
每列含义如下:
* rrqm/s, wrqm/s: 每秒读写请求的合并数量(OS会尽量读取和写入临近扇区)
* r/s, w/s: 每秒读写请求次数
* rsec/s, wsec/s: 每秒读写请求的字节数
* avgrq-sz: 每秒请求的队列大小
* avgqu-sz: 每秒请求的队列长度
* await: 从服务发起来返回信息共花费的平均服务时间
* svctm: 该值不必关注
* %util: 磁盘的利用率

### mpstat

mpstat 返回 CPU 的详细性能信息。

```sh
    root@debian:~# mpstat 3 5
    Linux 3.16.0-4-amd64 (debian)   09/26/2021      _x86_64_        (4 CPU)

    10:00:42 AM  CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
    10:00:45 AM  all    0.00    0.00    0.08    0.00    0.00    0.00    0.00    0.00    0.00   99.92
    10:00:48 AM  all    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
    10:00:51 AM  all    0.00    0.00    0.17    0.00    0.00    0.00    0.00    0.00    0.00   99.83
    10:00:54 AM  all    0.00    0.00    0.08    0.08    0.00    0.17    0.00    0.00    0.00   99.66
    10:00:57 AM  all    0.00    0.00    0.08    0.00    0.00    0.00    0.00    0.00    0.00   99.92
    Average:     all    0.00    0.00    0.08    0.02    0.00    0.03    0.00    0.00    0.00   99.87
```
最后一行会有一个运行期间的平均统计值，默认的 mpstat 会统计所有 CPU 的信息，如果只需要观察某一个 CPU，加上参数 -P n，n 为要观察的 core 的索引。

例如观察 CPU 0 的统计信息:
```sh
    root@debian:~# mpstat -P 0 3 5
    Linux 3.16.0-4-amd64 (debian)   09/26/2021      _x86_64_        (4 CPU)

    10:03:46 AM  CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
    10:03:49 AM    0    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
    10:03:52 AM    0    0.00    0.00    0.33    0.00    0.00    0.00    0.00    0.00    0.00   99.67
    10:03:55 AM    0    0.00    0.00    0.00    0.00    0.00    0.35    0.00    0.00    0.00   99.65
    10:03:58 AM    0    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
    10:04:01 AM    0    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
    Average:       0    0.00    0.00    0.07    0.00    0.00    0.07    0.00    0.00    0.00   99.87
```
以上输出的各列的含义如下:
* %usr: 用户花费的时间比例
* %nice: 特定优先级进程的 CPU 时间百分比
* %sys: 系统花费的时间比例
* %iowait: I/O等待
* %irq: 硬中断花费的 CPU 时间
* %soft: 软中断花费的 CPU 时间
* %steal,%guest: 这两个参数与虚拟机有关
* %idle: 空闲比率

### sar

sar 是性能统计非常重要的工具。sar 每隔一段时间进行一次统计，它的配置在 `/etc/cron.d/sysstat` 中，默认为 10 分钟。

```sh
    root@debian:~# cat /etc/cron.d/sysstat 
    # The first element of the path is a directory where the debian-sa1
    # script is located
    PATH=/usr/lib/sysstat:/usr/sbin:/usr/sbin:/usr/bin:/sbin:/bin

    # Activity reports every 10 minutes everyday
    5-55/10 * * * * root command -v debian-sa1 > /dev/null && debian-sa1 1 1

    # Additional run at 23:59 to rotate the statistics file
    59 23 * * * root command -v debian-sa1 > /dev/null && debian-sa1 60 2
```
可以调整统计信息的收集频率。

有些机器上，sar 并未开启数据收集，如下:
```sh
    root@debian:~# sar
    Cannot open /var/log/sysstat/sa26: No such file or directory
    Please check if data collecting is enabled
```
处理如下:
```sh
    root# vim /etc/default/sysstat        # 将 false 改为 true
    root# service sysstat restart
```

sar 的结果是基于历史的，即从开机到最后一次收集数据时的统计信息，在输出时默认使用 AM/PM 显示时间，可以在执行 sar 前强制使用 LANG=C 以使用 24 小时时间表示法显示时间。

sar 统计的维度很多。

1.汇总 CPU 状况

```sh
    sar -q
```

2.汇总 I/O 状况

```sh
    sar -b
```

3.历史数据汇总

```sh
    sar -q -f /var/log/sa/sa15 -s 22:00:00 -e 23:00:00
```
