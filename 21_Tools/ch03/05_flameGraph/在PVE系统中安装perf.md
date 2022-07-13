
pve 系统中执行:
```sh
    apt install linux-tools-common
```
安装完成后，执行 perf 的一些命令，会有如下警告:
```sh
WARNING: perf not found for kernel 5.4.34-1

  You may need to install the following packages for this specific kernel:
    linux-tools-5.4.34-1-pve
    linux-cloud-tools-5.4.34-1-pve

  You may also want to install one of the following packages to keep up to date:
    linux-tools-pve
    linux-cloud-tools-pve
WARNING: perf not found for kernel 5.4.34-1

  You may need to install the following packages for this specific kernel:
    linux-tools-5.4.34-1-pve
    linux-cloud-tools-5.4.34-1-pve

  You may also want to install one of the following packages to keep up to date:
    linux-tools-pve
    linux-cloud-tools-pve
ERROR: No stack counts found
```

尝试执行 `apt-get install linux-tools-5.4.34-1-pve` 后，输出显示并未找到相应的 package 。

解决方式如下。

1. apt 源文件中添加如下内容:
```sh
    deb http://download.proxmox.com/debian/pve buster pve-no-subscription
```
执行 `apt-get update` 更新源。

2. 更新源完成后，执行如下命令尝试搜索 pve 相关包
```sh
    apt-cache search pve
```

在 package 列表中搜索 '5.4.34-1' 字段。这里找到两个:
```sh
pve-headers-5.4.34-1-pve - The Proxmox PVE Kernel Headers
pve-kernel-5.4.34-1-pve - The Proxmox PVE Kernel Image
```
不管了，都装上:
```sh
    apt-get install pve-headers-5.4.34-1-pve
```

结果，安装太慢了，暂不知道结果。。。
