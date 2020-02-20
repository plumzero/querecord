


Tab 补全


## 说明
- 使用 2.6.26-2-686 内核版本进行测试；
- 本文件中出现的 磁盘、设备、device 同义；
- 使用 GRUB 0.97 (Grub Legacy)进行测试；

## 搜索可用磁盘分区
- grub> root (hd0,
   Possible partions are:
     Partition num: 0, Filesystem type is ext2fs, partition type 0x83
     Partition num: 4, Filesystem type unknown, partion type 0x82
## 查看 stage1 文件的磁盘位置
- grub> find /boot/grub/stage
   (hd0,0)

## grub 命令行引导
- 事先已经将内核镜像和 initrd 文件放置在 (hd0,0) 磁盘分区下
        grub> root (hd0,0)
         Filesystem type is ext2fs, partition type 0x83
- 设置引导文件加载磁盘及分区
        grub> setup (hd0,0)
         Checking if "/boot/grub/stage1" exists... yes
         Checking if "/boot/grub/stage2" exists... yes
         Checking if "/boot/grub/e2fs_stage1_5" exists... yes
         Running "embed /boot/grub/e2fs_stage1_5 (hd0,0)"... failed (this is not fatal)
         Running "embed /boot/grub/e2fs_stage1_5 (hd0,0)"... failed (this is not fatal)
         Running "install /boot/grub/stage1 (hd0,0) /boot/grub/stage2 p /boot/grub/menu.lst "... succeeded
        Done.
- 指定引导启动的内核镜像文件路径
        grub> kernel (hd0,0)/boot/vmlinuz-2.6.26-2-686 root=/dev/sda1 ro quiet
            [Linux-bzImage, setup=0x3000, size=0x16ce50]
  因为上面已经指定了引导设备，所以也可以不指定全路径
        grub> kernel /vmlinuz root=/dev/sda1 ro quiet
  根文件系统盘除了通过 root=/dev/sda1 指定之外，也可以通过 UUID 指定
        grub> kernel (hd0,0)/boot/vmlinuz-2.6.26-2-686 UUID=a169c4f3-05a6-4ee9-bb81-68e54f03eb1f ro quiet
  通过 blkid 命令获取设备的 UUID:
        blkid UUID
- 指定引导启动的 initrd 镜像文件路径
        grub> initrd (hd0,0)/boot/initrd.img-2.6.26-2-686
           [Linux-initrd @ 0x1f8ee000, 0x5e1f1e bytes]
  因为上面已经指定了引导设备，所以也可以不指定全路径
        grub> initrd /initrd
- 启动
        grub> boot

## 设备命名规则
- 命名规则及注意
        (fd0)
    + 以 ( 和 ) 进行包裹， fd 表示一个软盘，0 表示驱动号，驱动号从 0 开始；
    + 此表达式表示 GRUB 会使用整个软盘；
        (hd0, 1)
    + hd 表示硬盘，0 表示驱动号，硬盘驱动号从 0 开始。1 表示分区号，分区号从 0 开始；
    + 此表达式表示第 1 块硬盘的第 2 个分区，GRUB 将会使用此硬盘的部分分区，而不是整个硬盘；
        (hd0, 4)
    + 分区号从 4 开始(即第 5 个分区)，及之后的分区，均表示扩展分区；
GRUB 无法区分 IDE 和 SCSI 盘，一般 IDE 盘号比 SCSI 盘号要小，但也不尽然。
- 通过 grub 命令行访问磁盘分区和文件
    + 访问磁盘分区
            grub> root (
    <TAB> 补全显示磁盘、分区列表
    + 访问磁盘文件
            grub> (hd0,0)/boot/vmlinuz
    <TAB> 补全显示对应文件

## 引导装载的两种方法
- 直接引导: 支持 Linux, FreeBSD, NetBSD, OpenBSD，步骤如下:
    1. 设置 GRUB 的根设备(启动盘)
        grub> root (hd0,0)
        grub> setup (hd0,0)
    2. 加载内核镜像和 initrd 镜像
        grub> kernel /vmlinuz root=/dev/hda1 ro quiet
        grub> initrd /initrd
    3. 加载内核模块
    4. 运行
        grub> boot
- 间接引导(链式载入Chain-loading, Windows 系统引导时使用)，步骤如下:
    1. 设置 GRUB 的根设备分区
        grub> rootnoverify (hd0,0)
    2. 为该分区设置 active 标识
        grub> makeactive
    3. 加载引导程序
        grub> chainloader +1
    4. 运行
        grub> boot

## 回退系统
- Booting fallback systems
    https://www.gnu.org/software/grub/manual/legacy/Booting-fallback-systems.html#Booting-fallback-systems

## grub-install
        mke2fs /dev/fd0
        mount -t ext2 /dev/fd0 /mnt
        grub-install --root-directory=/mnt fd0
        umount /mnt