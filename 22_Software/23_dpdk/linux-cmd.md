

- 查看内核版本
  ```sh
    uname -r
  ```

- 查看 glibc 版本
  ```sh
    ldd --version
  ```

- 查看 CPU 是否支持大页操作
  ```sh
    cat /proc/cpuinfo | grep pse
    cat /proc/cpuinfo | grep pdpe1gb
  ```
  如果 pse 存在，则支持 2M 大页。如果 pdpe1gb 存在，则支持 1G 大页。

- 查看是否支持 HPET 特性
  ```sh
    cat /proc/timer_list | grep hpet
  ```
  
- 查看 NUMA 机器 Node 数量
  ```sh
    numactl --hardware
  ```
  输出示例如下:
  ```sh
    available: 1 nodes (0)
    node 0 cpus: 0 1 2 3
    node 0 size: 2047 MB
    node 0 free: 1491 MB
    node distances:
    node   0 
      0:  10 
  ```
  可以看到只有一个 Node 节点，管理 2GB 内存。空闲内存 1491 MB，说明内存还不是太紧张。
  如果 free 较小的话，就会产生抖动，影响性能，应该想办法解决。

  如果没有 `numactl` 命令，可以进入 `/sys/devices/system/node` 目录下查看节点个数。在另一台机器上测试:
  ```sh
    # ls
    has_cpu  has_memory  has_normal_memory  node0  node1  online  possible  power  ueve
  ```
  可以看到有两个节点，分别是 node0 和 node1 。



