
## 获取卷信息与状态

操作动态磁盘时，创建的是卷，而不是分区。简单地说，卷是可以直接用于存储数据的磁盘部分。

在单一驱动器上创建一个卷，称为简单卷。

对卷进行扩展，使其占据磁盘上所有空闲空间，这一过程创建了一个扩展卷。

创建一个跨越多个驱动器的卷，称为跨区卷。


## 卷信息与状态

示例
```
    diskpart
    DISKPART> list volume
```

输出说明

|    选项    | 描述 |
|:-----------|:-----|
| Volume ### | 卷编号，可以通过 select volume n 命令来选定待操作的卷 |
| LTR        | 卷的驱动器盘符 |
| Label      | 标签，卷标 |
| FS         | 文件系统类型，比如 CDUDF、FAT、FAT32 或 NTFS |
| Type       | 布局类型 |
| Size       | 卷的总存储容量 |
| Status     | 卷的状态，正常，失败、冗余等 |
| Info       | 提供了关于该卷的一些附加信息，比如该卷为系统卷等 |


## 创建简单卷

示例
```
    diskpart
    DISKPART> list disk      // 检查磁盘空闲空间
        磁盘 ###  状态           大小     可用     Dyn  Gpt
        --------  -------------  -------  -------  ---  ---
        磁盘 0    联机              238 GB  1024 KB
        磁盘 1    联机              111 GB    50 GB *
    // 磁盘1一共有111GB空间，其中空闲卷空间50GB。
    DISKPART> create volume simple size=25600 disk=1
    // 创建简单卷，大小为25GB,位于磁盘1上。创建卷之后，焦点将自动地被放置到其上，表示该卷已被选定，但该卷尚无盘符或挂载点。
    DISKPART> assign letter=I
    DISKPART> format fs=ntfs label='Dyn'
```


## 扩展简单卷

如果某简单卷需要更多磁盘空间，有两种方式可以对其进行扩展。一种是在同一磁盘上对其进行扩展，所得的卷叫做扩展卷；一种是在其他磁盘上进行扩展，所得的卷叫做跨区卷。对这两种情况，卷都必须格式化为NTFS。

示例
```
    diskpart
    DISKPART> list disk
    DISKPART> list volume
    DISKPART> select volume 5
    DISKPART> extend size=10240             // 扩展卷。对卷进行扩展，增加大小为 10240 MB
        DISKPART> extend size=10240 disk=1  // 跨区卷。如果卷在disk 0上，将其扩展到disk 1上，扩展区域为 10240 MB
```


## 删除卷

在动态磁盘上，不应该使用 `Delete Partition` 命令，因为该命令将删除磁盘上所有动态卷。如果需要删除动态磁盘上焦点所在卷，可以使用 `Delete Volume` 命令。

不能使用 `Delete Volume` 命令删除系统卷或引导卷，也不能删除包含活跃页面文件或崩溃转储文件的卷。

示例
```
    DISKPART> list volume
    DISKPART> select volume 5
    DISKPART> delete volume
```
