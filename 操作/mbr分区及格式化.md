
## 参考
[Linux下的磁盘分区和逻辑卷](https://www.cnblogs.com/lbole/p/8904298.html)


## 关于 MBR 分区

- MBR 分区类说明
	+ MBR支持最大2TB磁盘，它无法处理大于2TB容量的磁盘。
	+ MBR格式的磁盘分区概念有基本分区(primary partion)、扩展分区(extension partion)
	  和逻辑分区。
	+ 主分区总数不能大于 4 个，其中最多只能有一个扩展分区。基本分区可以马上被挂载使
	  用但不能再分区，扩展分区必须再进行二次分区后才能挂载。
	+ 扩展分区下的二次分区被称之为逻辑分区，逻辑分区数量限制视磁盘类型而定。如果是
	  SCSI 接口硬盘则最多只能有 15 (其中扩展分区不能直接使用所以不计算)个分区，其中
	  主分区最多 4 个，逻辑分区最多 12 个。IDE 接口硬盘最多只能有 63 (其中扩展分区
	  不能直接使用所以不计算)个分区，其中主分区最多 4 个，逻辑分区最多 60 个。

- 在非交互式界面下显示当前磁盘分区信息
  ```fdisk
	fdisk -l
	fdisk -l /dev/sda
  ```
  输出结果如下:
  ```shell
	Disk /dev/sda: 53.7 GB, 53687091200 bytes
	255 heads, 63 sectors/track, 6527 cylinders, total 104857600 sectors
	Units = sectors of 1 * 512 = 512 bytes
	Sector size (logical/physical): 512 bytes / 512 bytes
	I/O size (minimum/optimal): 512 bytes / 512 bytes
	Disk identifier: 0x0002777f

	   Device Boot      Start         End      Blocks   Id  System
	/dev/sda1   *        2048   102762495    51380224   83  Linux
	/dev/sda2       102762496   104857599     1047552    5  Extended
	/dev/sda5       102764544   104857599     1046528   82  Linux swap / Solaris
  ```
  磁盘分区文件目录在 /dev/ 下:
  ```shell
	ls /dev/sda*
  ```
  输出结果如下:
  ```shell
	/dev/sda  /dev/sda1  /dev/sda4  /dev/sda
  ```

## 在 VM 虚拟机 ubuntu 14.04 上对磁盘进行 MBR 分区

+ 当前分区列表
  ```shell
	fdisk /dev/sda
	Command (m for help): n
	Partition type:
	   p   primary (1 primary, 1 extended, 2 free)
	   l   logical (numbered from 5)
	Select (default p): 
  ```
  目前只分配了一个主分区(primary)和一个扩展分区(extended)。还有两个 free 可以用来预留
  添加分区作为主分区使用。不管是否有 free，逻辑分区号必须从 5 开始，且是由系统自动递增
  的。如下:
  ```shell
	Command (m for help): p

	Disk /dev/sda: 53.7 GB, 53687091200 bytes
	255 heads, 63 sectors/track, 6527 cylinders, total 104857600 sectors
	Units = sectors of 1 * 512 = 512 bytes
	Sector size (logical/physical): 512 bytes / 512 bytes
	I/O size (minimum/optimal): 512 bytes / 512 bytes
	Disk identifier: 0x0002777f

	   Device Boot      Start         End      Blocks   Id  System
	/dev/sda1   *        2048   102762495    51380224   83  Linux
	/dev/sda2       102764542   104855551     1045505    5  Extended
	/dev/sda5       102764544   104855551     1045504   82  Linux swap / Solaris
  ```
  /dev/sda1、/dev/sda2 和 /dev/sda5 分别对应主分区 primary、扩展分区 extended 和扩展分
  区下的一个逻辑分区。
  注意: 除非特别说明，否则以下的分区操作均是在该分区列表下进行的。

+ 说明
  如果想要新添加一个分区，以当前分区列表为例，可以:
	+ 添加主分区 /dev/sda3 或 /dev/sda4 。(如果主分区已满，达到 4 个，则必须先删除一个
	  主分区，再创建一个扩展分区，之后再在此扩展分区下创建逻辑分区。)
	+ 在扩展分区 /dev/sda2 下创建新的逻辑分区；

+ 添加主分区
  ```shell
	Command (m for help): n
	Partition type:
	   p   primary (1 primary, 1 extended, 2 free)
	   l   logical (numbered from 5)
	Select (default p): p
	Partition number (1-4, default 3): 3
	First sector (102762496-104857599, default 102762496): 
	Using default value 102762496
	Last sector, +sectors or +size{K,M,G} (102762496-102764541, default 102764541): 
	Using default value 102764541
  ```
  选择 p (primary)添加主分区，分区号范围为 1-4, 因为 1 和 2 已经被分配，所以只能选择 3
  或 4 ,这里选择缺省的 3 。
  block 大小和截止扇区按缺省处理(按 Enter 键)。
  添加主分区后的分区列表如下:
  ```shell
	Command (m for help): p

	Disk /dev/sda: 53.7 GB, 53687091200 bytes
	255 heads, 63 sectors/track, 6527 cylinders, total 104857600 sectors
	Units = sectors of 1 * 512 = 512 bytes
	Sector size (logical/physical): 512 bytes / 512 bytes
	I/O size (minimum/optimal): 512 bytes / 512 bytes
	Disk identifier: 0x0002777f

	   Device Boot      Start         End      Blocks   Id  System
	/dev/sda1   *        2048   102762495    51380224   83  Linux
	/dev/sda2       102764542   104855551     1045505    5  Extended
	/dev/sda3       102762496   102764541        1023   83  Linux
	/dev/sda5       102764544   104855551     1045504   82  Linux swap / Solaris
  ```
  添加完成后需要对所作的更改进行保存后才能生效:
  ```shell
	Command (m for help): w
	The partition table has been altered!

	Calling ioctl() to re-read partition table.

	WARNING: Re-reading the partition table failed with error 16: Device or resource busy.
	The kernel still uses the old table. The new table will be used at
	the next reboot or after you run partprobe(8) or kpartx(8)
	Syncing disks.
  ```

+ 删除扩展分区
  删除扩展分区后，其下的所有逻辑分区也会被删除。以删除 /dev/sda2 为例:
  ```shell
	Command (m for help): n
	Partition type:
	   p   primary (1 primary, 0 extended, 3 free)
	   e   extended
	Select (default p): 
  ```
  删除后，系统现在只有一个主分区了。删除后的分区列表如下:
  ```shell
	Command (m for help): p

	Disk /dev/sda: 53.7 GB, 53687091200 bytes
	255 heads, 63 sectors/track, 6527 cylinders, total 104857600 sectors
	Units = sectors of 1 * 512 = 512 bytes
	Sector size (logical/physical): 512 bytes / 512 bytes
	I/O size (minimum/optimal): 512 bytes / 512 bytes
	Disk identifier: 0x0002777f

	   Device Boot      Start         End      Blocks   Id  System
	/dev/sda1   *        2048   102762495    51380224   83  Linux
  ```
  删除主分区或逻辑分区的操作与删除扩展分区的操作是相同的，不作演示。

+ 添加扩展分区
  在执行完**删除扩展分区**后，再重新添加扩展分区:
  ```shell
	Command (m for help): n
	Partition type:
	   p   primary (1 primary, 0 extended, 3 free)
	   e   extended
	Select (default p): e
	Partition number (1-4, default 2): 4
	First sector (102762496-104857599, default 102762496): 
	Using default value 102762496
	Last sector, +sectors or +size{K,M,G} (102762496-104857599, default 104857599): 
	Using default value 104857599
  ```
  这里选择 4 ，其他按缺省处理，执行后的分区列表如下:
  ```shell
	Command (m for help): p

	Disk /dev/sda: 53.7 GB, 53687091200 bytes
	255 heads, 63 sectors/track, 6527 cylinders, total 104857600 sectors
	Units = sectors of 1 * 512 = 512 bytes
	Sector size (logical/physical): 512 bytes / 512 bytes
	I/O size (minimum/optimal): 512 bytes / 512 bytes
	Disk identifier: 0x0002777f

	   Device Boot      Start         End      Blocks   Id  System
	/dev/sda1   *        2048   102762495    51380224   83  Linux
	/dev/sda4       102762496   104857599     1047552    5  Extended
  ```

+ 创建逻辑分区
  在执行完**添加扩展分区**后，再在扩展分区中创建逻辑分区:
  ```shell
	Command (m for help): n
	Partition type:
	   p   primary (1 primary, 1 extended, 2 free)
	   l   logical (numbered from 5)
	Select (default p): l
	Adding logical partition 5
	First sector (102764544-104857599, default 102764544): 
	Using default value 102764544
	Last sector, +sectors or +size{K,M,G} (102764544-104857599, default 104857599): 
	Using default value 104857599
  ```
  选择 l (logical)，其他按缺省处理，执行后的分区列表如下:
  ```shell
	Command (m for help): p

	Disk /dev/sda: 53.7 GB, 53687091200 bytes
	255 heads, 63 sectors/track, 6527 cylinders, total 104857600 sectors
	Units = sectors of 1 * 512 = 512 bytes
	Sector size (logical/physical): 512 bytes / 512 bytes
	I/O size (minimum/optimal): 512 bytes / 512 bytes
	Disk identifier: 0x0002777f

	   Device Boot      Start         End      Blocks   Id  System
	/dev/sda1   *        2048   102762495    51380224   83  Linux
	/dev/sda4       102762496   104857599     1047552    5  Extended
	/dev/sda5       102764544   104857599     1046528   83  Linux
  ```
  
+ 转换分区类型
  在执行完**创建逻辑分区**后，将新创建的逻辑分区 /dev/sda5 类型由 Linux 普通分区
  (System=Linux, Id=83)转换为 swap 分区(System=Linux swap/Solaris Id=82)。
  Linux 分区类型可以通过如下命令执行查看:
  ```shell
	Command (m for help): l

	 0  Empty           24  NEC DOS         81  Minix / old Lin bf  Solaris        
	 1  FAT12           27  Hidden NTFS Win 82  Linux swap / So c1  DRDOS/sec (FAT-
	 2  XENIX root      39  Plan 9          83  Linux           c4  DRDOS/sec (FAT-
	 3  XENIX usr       3c  PartitionMagic  84  OS/2 hidden C:  c6  DRDOS/sec (FAT-
	 4  FAT16 <32M      40  Venix 80286     85  Linux extended  c7  Syrinx         
	 5  Extended        41  PPC PReP Boot   86  NTFS volume set da  Non-FS data    
	 6  FAT16           42  SFS             87  NTFS volume set db  CP/M / CTOS / .
	 7  HPFS/NTFS/exFAT 4d  QNX4.x          88  Linux plaintext de  Dell Utility   
	 8  AIX             4e  QNX4.x 2nd part 8e  Linux LVM       df  BootIt         
	 9  AIX bootable    4f  QNX4.x 3rd part 93  Amoeba          e1  DOS access     
	 a  OS/2 Boot Manag 50  OnTrack DM      94  Amoeba BBT      e3  DOS R/O        
	 b  W95 FAT32       51  OnTrack DM6 Aux 9f  BSD/OS          e4  SpeedStor      
	 c  W95 FAT32 (LBA) 52  CP/M            a0  IBM Thinkpad hi eb  BeOS fs        
	 e  W95 FAT16 (LBA) 53  OnTrack DM6 Aux a5  FreeBSD         ee  GPT            
	 f  W95 Ext'd (LBA) 54  OnTrackDM6      a6  OpenBSD         ef  EFI (FAT-12/16/
	10  OPUS            55  EZ-Drive        a7  NeXTSTEP        f0  Linux/PA-RISC b
	11  Hidden FAT12    56  Golden Bow      a8  Darwin UFS      f1  SpeedStor      
	12  Compaq diagnost 5c  Priam Edisk     a9  NetBSD          f4  SpeedStor      
	14  Hidden FAT16 <3 61  SpeedStor       ab  Darwin boot     f2  DOS secondary  
	16  Hidden FAT16    63  GNU HURD or Sys af  HFS / HFS+      fb  VMware VMFS    
	17  Hidden HPFS/NTF 64  Novell Netware  b7  BSDI fs         fc  VMware VMKCORE 
	18  AST SmartSleep  65  Novell Netware  b8  BSDI swap       fd  Linux raid auto
	1b  Hidden W95 FAT3 70  DiskSecure Mult bb  Boot Wizard hid fe  LANstep        
	1c  Hidden W95 FAT3 75  PC/IX           be  Solaris boot    ff  BBT            
	1e  Hidden W95 FAT1 80  Old Minix      
  ```
  Linux 支持的分区类型很多，但最常使用的分区类型只有下面几种
| ID |  分区类型  | 描述 |
|:--:|:----------:|:-----:|
| 83 | Linux      | Linux 普通分区 |
| fd | Linux raid auto | RAID 使用的分区 |
| 8e | Linux LVM | LVM 使用的分区 |
| 82 | Linux swap/Solaris | swap 分区 |
  接下来进行正式的分区类型转换操作:
  ```shell
	Command (m for help): t
	Partition number (1-5): 5
	Hex code (type L to list codes): 82
	Changed system type of partition 5 to 82 (Linux swap / Solaris)
  ```
  执行后的分区列表如下:
  ```shell
	Command (m for help): p

	Disk /dev/sda: 53.7 GB, 53687091200 bytes
	255 heads, 63 sectors/track, 6527 cylinders, total 104857600 sectors
	Units = sectors of 1 * 512 = 512 bytes
	Sector size (logical/physical): 512 bytes / 512 bytes
	I/O size (minimum/optimal): 512 bytes / 512 bytes
	Disk identifier: 0x0002777f

	   Device Boot      Start         End      Blocks   Id  System
	/dev/sda1   *        2048   102762495    51380224   83  Linux
	/dev/sda4       102762496   104857599     1047552    5  Extended
	/dev/sda5       102764544   104857599     1046528   82  Linux swap / Solaris
  ```
 
+ 创建指定大小容量的逻辑分区
  有时需要在扩展分区下创建新的逻辑分区 B ，但在创建时系统却提示没有空间了:
  ```shell
	Command (m for help): n
	Partition type:
	   p   primary (1 primary, 1 extended, 2 free)
	   l   logical (numbered from 5)
	Select (default p): l
	Adding logical partition 6
	No free sectors available
  ```
  其中一个办法是回收(就是删除)多余空间的逻辑分区 A ，并将 A 再分为 A' 和 B。
  重新分区前:
  ```shell
	Command (m for help): p

	Disk /dev/sda: 53.7 GB, 53687091200 bytes
	255 heads, 63 sectors/track, 6527 cylinders, total 104857600 sectors
	Units = sectors of 1 * 512 = 512 bytes
	Sector size (logical/physical): 512 bytes / 512 bytes
	I/O size (minimum/optimal): 512 bytes / 512 bytes
	Disk identifier: 0x0002777f

	   Device Boot      Start         End      Blocks   Id  System
	/dev/sda1   *        2048   102762495    51380224   83  Linux
	/dev/sda4       102762496   104857599     1047552    5  Extended
  ```
  通过指定结束扇区来重新划分逻辑分区 A'，执行如下:
  ```shell
	Command (m for help): n
	Partition type:
	   p   primary (1 primary, 1 extended, 2 free)
	   l   logical (numbered from 5)
	Select (default p): l
	Adding logical partition 5
	First sector (102764544-104857599, default 102764544): 
	Using default value 102764544
	Last sector, +sectors or +size{K,M,G} (102764544-104857599, default 104857599): 103000000

	Command (m for help): p

	Disk /dev/sda: 53.7 GB, 53687091200 bytes
	255 heads, 63 sectors/track, 6527 cylinders, total 104857600 sectors
	Units = sectors of 1 * 512 = 512 bytes
	Sector size (logical/physical): 512 bytes / 512 bytes
	I/O size (minimum/optimal): 512 bytes / 512 bytes
	Disk identifier: 0x0002777f

	   Device Boot      Start         End      Blocks   Id  System
	/dev/sda1   *        2048   102762495    51380224   83  Linux
	/dev/sda4       102762496   104857599     1047552    5  Extended
	/dev/sda5       102764544   103000000      117728+  83  Linux
  ```
  利用剩余的空间创建新的逻辑分区 B，执行如下:
  ```shell
	Command (m for help): n
	Partition type:
	   p   primary (1 primary, 1 extended, 2 free)
	   l   logical (numbered from 5)
	Select (default p): l
	Adding logical partition 6
	First sector (103002049-104857599, default 103002049): 
	Using default value 103002049
	Last sector, +sectors or +size{K,M,G} (103002049-104857599, default 104857599): 
	Using default value 104857599

	Command (m for help): p

	Disk /dev/sda: 53.7 GB, 53687091200 bytes
	255 heads, 63 sectors/track, 6527 cylinders, total 104857600 sectors
	Units = sectors of 1 * 512 = 512 bytes
	Sector size (logical/physical): 512 bytes / 512 bytes
	I/O size (minimum/optimal): 512 bytes / 512 bytes
	Disk identifier: 0x0002777f

	   Device Boot      Start         End      Blocks   Id  System
	/dev/sda1   *        2048   102762495    51380224   83  Linux
	/dev/sda4       102762496   104857599     1047552    5  Extended
	/dev/sda5       102764544   103000000      117728+  83  Linux
	/dev/sda6       103002049   104857599      927775+  83  Linux
  ```
  说明: 这里没有多余空间进行分区创建的原因可能是在安装系统镜像时，只指定
  
## 在 VM 虚拟机 ubuntu 14.04 上添加新的虚拟磁盘并对该磁盘进行 MBR 分区
- 在添加新磁盘之前，磁盘设备信息如下:
  ```shell
	root@ubuntu:~# ls -al /dev/sd*
	brw-rw---- 1 root disk 8, 0 Jan 20 03:10 /dev/sda
	brw-rw---- 1 root disk 8, 1 Jan 20 03:10 /dev/sda1
	brw-rw---- 1 root disk 8, 4 Jan 20 03:10 /dev/sda4
	brw-rw---- 1 root disk 8, 5 Jan 20 03:10 /dev/sda5
  ```
  只有一个 /dev/sda 设备。
- 添加新的虚拟磁盘后，重启设备，磁盘设备信息如下:
  ```shell
	root@ubuntu:~# ls -al /dev/sd*
	brw-rw---- 1 root disk 8,  0 Jan 20 03:15 /dev/sda
	brw-rw---- 1 root disk 8,  1 Jan 20 03:15 /dev/sda1
	brw-rw---- 1 root disk 8,  4 Jan 20 03:15 /dev/sda4
	brw-rw---- 1 root disk 8,  5 Jan 20 03:15 /dev/sda5
	brw-rw---- 1 root disk 8, 16 Jan 20 03:15 /dev/sdb
  ```
  可以看到，增加了一个新的设备 /dev/sdb ，不过还未对其进行分区。
  通过 **fdisk -l** 命令可以查看整个磁盘分区信息。

- 磁盘分区操作
  ``` shell
	root@ubuntu:~# fdisk /dev/sdb
	Device contains neither a valid DOS partition table, nor Sun, SGI or OSF disklabel
	Building a new DOS disklabel with disk identifier 0xac70583d.
	Changes will remain in memory only, until you decide to write them.
	After that, of course, the previous content won't be recoverable.

	Warning: invalid flag 0x0000 of partition table 4 will be corrected by w(rite)

	Command (m for help): n
	Partition type:
	   p   primary (0 primary, 0 extended, 4 free)
	   e   extended
	Select (default p): p
	Partition number (1-4, default 1): 1
	First sector (2048-41943039, default 2048): 
	Using default value 2048
	Last sector, +sectors or +size{K,M,G} (2048-41943039, default 41943039): 1000000

	Command (m for help): p

	Disk /dev/sdb: 21.5 GB, 21474836480 bytes
	255 heads, 63 sectors/track, 2610 cylinders, total 41943040 sectors
	Units = sectors of 1 * 512 = 512 bytes
	Sector size (logical/physical): 512 bytes / 512 bytes
	I/O size (minimum/optimal): 512 bytes / 512 bytes
	Disk identifier: 0x3b9af01c

	   Device Boot      Start         End      Blocks   Id  System
	/dev/sdb1            2048     1000000      498976+  83  Linux

	Command (m for help): w
	The partition table has been altered!

	Calling ioctl() to re-read partition table.
	Syncing disks.
  ```
  根据自己的需求，进行相应的磁盘分区操作。
  最后系统总的分区列表如下:
  ```shell
	root@ubuntu:/# fdisk -l

	Disk /dev/sdb: 21.5 GB, 21474836480 bytes
	64 heads, 2 sectors/track, 327680 cylinders, total 41943040 sectors
	Units = sectors of 1 * 512 = 512 bytes
	Sector size (logical/physical): 512 bytes / 512 bytes
	I/O size (minimum/optimal): 512 bytes / 512 bytes
	Disk identifier: 0x3b9af01c

	   Device Boot      Start         End      Blocks   Id  System
	/dev/sdb1            2048     1000000      498976+  83  Linux

	Disk /dev/sda: 53.7 GB, 53687091200 bytes
	255 heads, 63 sectors/track, 6527 cylinders, total 104857600 sectors
	Units = sectors of 1 * 512 = 512 bytes
	Sector size (logical/physical): 512 bytes / 512 bytes
	I/O size (minimum/optimal): 512 bytes / 512 bytes
	Disk identifier: 0x0002777f

	   Device Boot      Start         End      Blocks   Id  System
	/dev/sda1   *        2048   102762495    51380224   83  Linux
	/dev/sda4       102762496   104857599     1047552    5  Extended
	/dev/sda5       102764544   104857599     1046528   82  Linux swap / Solaris
  ```

## 分区格式化
- 对磁盘进行分区后，还需要对分区进行格式化并创建文件系统。一个分区只有建立了某种文件系统
  以后，这个分区才能使用。
- 对磁盘分区 /dev/sdb1 格式化并创建文件系统 ext4
  ```shell
	root@ubuntu:/# mkfs -t ext4 /dev/sdb1
	mke2fs 1.42.9 (4-Feb-2014)
	Filesystem label=
	OS type: Linux
	Block size=1024 (log=0)
	Fragment size=1024 (log=0)
	Stride=0 blocks, Stripe width=0 blocks
	124928 inodes, 498976 blocks
	24948 blocks (5.00%) reserved for the super user
	First data block=1
	Maximum filesystem blocks=67633152
	61 block groups
	8192 blocks per group, 8192 fragments per group
	2048 inodes per group
	Superblock backups stored on blocks: 
			8193, 24577, 40961, 57345, 73729, 204801, 221185, 401409

	Allocating group tables: done                            
	Writing inode tables: done                            
	Creating journal (8192 blocks): done
	Writing superblocks and filesystem accounting information: done 
  ```

## 挂载和挂载文件系统
- 假设系统所处的当前磁盘为 O, 新添加的磁盘为 N，此时磁盘虽已添加，且已经分区和格式化，但
  在当前系统里没有办法直接访问磁盘 N。
  可以将磁盘 N 挂载到当前系统的一个文件下，之后进行访问。
- 将文件系统 /dev/sdb1 挂载到当前系统的一个目录下
  ```shell
	mkdir /newdev
	mount /dev/sdb1 /newdev
  ```
  可以通过 df 命令查看是否挂载成功:
  ```shell
	root@ubuntu:~# df -h
	Filesystem      Size  Used Avail Use% Mounted on
	udev            474M  4.0K  474M   1% /dev
	tmpfs            98M  1.1M   97M   2% /run
	/dev/sda1        49G   28G   19G  61% /
	none            4.0K     0  4.0K   0% /sys/fs/cgroup
	none            5.0M     0  5.0M   0% /run/lock
	none            488M  144K  488M   1% /run/shm
	none            100M   32K  100M   1% /run/user
	/dev/sdb1       464M  2.3M  434M   1% /newdev
  ```
  可以看出 Filesystem 项下有 /dev/sdb1 ，表示挂载成功了。
- 卸载文件系统 
  ```shell
	umount /dev/sdb1
	root@ubuntu:~# df -h
	Filesystem      Size  Used Avail Use% Mounted on
	udev            474M  4.0K  474M   1% /dev
	tmpfs            98M  1.1M   97M   2% /run
	/dev/sda1        49G   28G   19G  61% /
	none            4.0K     0  4.0K   0% /sys/fs/cgroup
	none            5.0M     0  5.0M   0% /run/lock
	none            488M  144K  488M   1% /run/shm
	none            100M   32K  100M   1% /run/user
  ```
  
## 关于 UUID
