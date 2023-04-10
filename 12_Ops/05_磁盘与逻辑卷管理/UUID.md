
### UUID 简介

- UUID(Universally Unique IDentifier，通用唯一标识符)，其目的是让分散式系统中的所有元素都能有一个唯一的辨识信息，而不需要通过中央控制端来做辨识信息的指定。
- UUID 是指在一台机器上生成的数字，它保证对在同一时空中的所有机器都是唯一的，因为 UUID 的计算用到了以太网卡地址、纳秒级时间、芯片 ID 码和许多可能的数字。
- UUID 的标准型式包含 32 个 16 进位数字，以连字号分为五段，形式为 "8-4-4-4-12" 的 32 个字符。
  
### UUID 查看

在 GRUB2 中，现在可以识别 UUID，查看 `/boot/grub2/grub.cfg` 文件。
```s
  menuentry 'Red Hat Enterprise Linux Server (3.10.0-862.el7.x86_64) 7.5 (Maipo)' --class red --class gnu-linux --class gnu --class os --unrestricted $menuentry_id_option 'gnulinux-3.10.0-862.el7.x86_64-advanced-b03ca2e2-68b3-41fb-a4e1-5ac9f09233be' {
    load_video
    set gfxpayload=keep
    insmod gzio
    insmod part_msdos
    insmod xfs
    set root='hd0,msdos1'
    if [ x$feature_platform_search_hint = xy ]; then
      search --no-floppy --fs-uuid --set=root --hint-bios=hd0,msdos1 --hint-efi=hd0,msdos1 --hint-baremetal=ahci0,msdos1 --hint='hd0,msdos1'  dc98ac5d-ce6e-40f2-8807-361ce92f1de3
    else
      search --no-floppy --fs-uuid --set=root dc98ac5d-ce6e-40f2-8807-361ce92f1de3
    fi
    linux16 /vmlinuz-3.10.0-862.el7.x86_64 root=UUID=b03ca2e2-68b3-41fb-a4e1-5ac9f09233be ro crashkernel=auto rhgb quiet net.ifnames=0 biosdevname=0 
    initrd16 /initramfs-3.10.0-862.el7.x86_64.img
  }
```

另外，可以通过查看磁盘分区 UUID 来得到，可以通过查看 /dev/disk/by-uuid 目录和 blkid 命令来实现。

以当前磁盘分区列表作为示例查看:
```s
  [root@localhost by-uuid]# fdisk -l

  Disk /dev/sda: 85.9 GB, 85899345920 bytes, 167772160 sectors
  Units = sectors of 1 * 512 = 512 bytes
  Sector size (logical/physical): 512 bytes / 512 bytes
  I/O size (minimum/optimal): 512 bytes / 512 bytes
  Disk label type: dos
  Disk identifier: 0x000c61b0

      Device Boot      Start         End      Blocks   Id  System
  /dev/sda1   *        2048      616447      307200   83  Linux
  /dev/sda2          616448     8744959     4064256   82  Linux swap / Solaris
  /dev/sda3         8744960   167772159    79513600   83  Linux
```
- 查看 /dev/disk/by-uuid 目录
  ```s
    [root@localhost by-uuid]# ls -l /dev/disk/by-uuid/
    total 0
    lrwxrwxrwx. 1 root root 10 Jan 20 00:25 b03ca2e2-68b3-41fb-a4e1-5ac9f09233be -> ../../sda3
    lrwxrwxrwx. 1 root root 10 Jan 20 00:25 dc98ac5d-ce6e-40f2-8807-361ce92f1de3 -> ../../sda1
    lrwxrwxrwx. 1 root root 10 Jan 20 00:25 eb65205f-6b99-4261-9e3a-5154ddf43c4e -> ../../sda2
  ```
- 通过 blkid 命令查看
  ```s
    [root@localhost by-uuid]# blkid /dev/sda1 /dev/sda2 /dev/sda3
    /dev/sda1: UUID="dc98ac5d-ce6e-40f2-8807-361ce92f1de3" TYPE="xfs" 
    /dev/sda2: UUID="eb65205f-6b99-4261-9e3a-5154ddf43c4e" TYPE="swap" 
    /dev/sda3: UUID="b03ca2e2-68b3-41fb-a4e1-5ac9f09233be" TYPE="xfs" 
  ```
可以看出，得到的结果是相等的。
- 磁盘分区中扩展分区是没有 UUID ，它是一个虚拟的概念，不是实体设备。
