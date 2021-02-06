
REM How to Run it 	-> 	diskpart /S disk2config.bat

REM Select disk 2
selete disk 2

REM Create the primary partiton on the disk and assign the drive letter
create partition primary size=4096 assign letter=s
format fs=ntfs label="primary"

REM Create extended partition with 2 logical drivers
create partition extended size=4096

create partition logical size=2048
assign letter=u
format fs=ntfs label="extended1"

create partition logical size=2047
assign letter=v
format fs=ntfs label="extended2"

在 disk 2 创建了主分区与扩展分区。
主分区大小设置为 4096MB, 盘符设置为 S, 并使用 NTFS 文件系统进行格式化。
扩展分区大小为 4096MB, 分为两个逻辑分区。第一个逻辑分区大小设置为 2048MB, 盘符为 U, 使用 NTFS 文件系统进行格式化；第二个逻辑分区大小设置为 2048MB, 盘符为 U, 使用 NTFS 文件系统进行格式化。