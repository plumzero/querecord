
### 设置 WAL 归档

运行的 PostgreSQL 系统会产生长序列的 WAL 记录，系统会将这个长序列物理性地分成多个 WAL 段文件，缺省情况下每个段文件大小为 16MB 。段文件以数字命名，这些数字说明了其各自在长序列中所处的位置。

系统不会无限制地创建段文件。如果段文件达到一定数量后，系统会将较早创建的段文件重命名为最新的数字名称并写入最新的 WAL 序列。

对 WAL 进行归档，就是定位每个写入完毕的 WAL 段文件，并在系统下次重写这些文件之前，将它们保存到某个安全的地方。

开启 WAL 归档需要对 `postgresql.con` 中的参数进行如下配置:

| 参数配置 | 说明 | 生效方式 |
|:--------|:-----|:--------|
| wal_level = replica | 获取足够的 WAL 信息 | 重启 |
| archive_mode = on | 开启归档模式 | 重启 |
| archive_command = 'test ! -f /path/to/archivedir/%f && cp %p /path/to/archivedir/%f' | 指定归档命令，这里是将 WAL 归档到 `/path/to/archivedir` 目录下 | 重载 |

关于 `/path/to/archivedir`，这里是 `/pgdata/13/archive_wals`。

参数配置完成之后，重新启动 PostgreSQL 数据库，这个时候系统会将 `data/pg_wal/` 目录下的 WAL 文件归档到 `/path/to/archivedir` 下。

归档命令(archive command)会在当前 PostgreSQL 数据库服务器运行用户(一般是超级用户 postgres)的权限下执行。要确保归档命令执行完毕后的返回值为 0 时表示成功，此时 PostgreSQL 会假定文件归档成功，并会移除相关文件，循环写入。如果返回值非 0，那么 PostgreSQL 会认为归档失败，此后会周期性尝试执行直到成功。

归档命令只操作完整的 WAL 段文件，如果不完整，会延迟归档直到事务的完成。可以通过指定配置 `postgresql.conf` 中的 `archive_timeout` 参数来设置服务器切换到另一个 WAL 段文件的超时，超时不宜太短，可以按分钟计。也可以在 PostgreSQL 命令行环境中执行如下命令进行强制手动 WAL 切换:
```sql
    mydb=# SELECT pg_switch_wal();
    pg_switch_wal 
    ---------------
    1/D59B77E8
    (1 row)
```


### 制作基础备份

`postgresql.conf` 参数配置:
* `full_page_writes = on`: 开启全页写模式

使用 `pg_basebackup` 命令进行基础备份，示例如下:
```shell
    postgres$: pg_basebackup -Ft -Pv -Xf -z -Z5 -p 5432 -D /path/to/backups
```
`-D` 指定备份保存的目录，这里是 `/pgdata/10/backups`。顺利的话，会在这个目录下面产生一个 base.tar.gz 文件，这个文件就是基础备份。

为了使用这个基础备份，需要保存所有在备份期间或这之后产生的 WAL 段文件。基础备份进程会在 WAL 产生的地方创建一个备份历史文件(backup history file)。比如 `0000000100000000000000D2.00000028.backup`，`0000000100000000000000D2` 表示在基础备份之后产生的第一个 WAL 段文件，这也是应该归档的首个文件。数字名称上比这个文件小的 WAL 段文件都是这个基础备份之前的文件，可以删除掉。


### 恢复

1.确保数据库服务器关闭。
2.如果磁盘空间足够，可以将服务器集簇的 `data` 目录以及表空间进行备份以防不测。如果磁盘不足，至少也应该将集簇下的 `pg_wal` 子目录进行备份。
3.移除集簇 `data` 目录下及表空间下的所有文件或目录。
4.在超级用户(postgres，而不是 root)权限下，从基础备份中恢复数据库文件，并移除 `pg_wal/` 目录下的所有文件，之后将之前归档的 WAL 段文件拷贝到 `pg_wal/` 目录下。
5.设置 `postgresql.conf` 中的恢复配置选项，并在集簇 `data` 目录下创建一个名为 `recovery.signal` 的文件。可能的话，临时修改 `pg_hba.conf` 文件保证在恢复期间避免其他用户对数据库的访问。
6.开启服务器。这个时候服务器将进入恢复模式，它会读取需要的归档 WAL 文件。如果恢复过程中因为外部错误终止，服务器会重启并继续恢复。恢复完成后，`recovery.signal`文件将被移除，这时就开始进行正常的数据库操作。
7.对数据库内容进行检查，确保已经恢复到自己期望的状态。如果是，修改 `pg_hba.conf` 文件允许其他用户进行访问。

恢复过程的关键在于设置恢复配置选项。

如果恢复过程中出现了损坏的 WAL 数据，恢复过程会中止在该点，数据库后续也将不会启动。这种情况下，可以从起点开始重启恢复进程，同时指定一个在损坏点之前的 `recovery target` 以保证可以完成在这之间的恢复。

为了开启服务器的目标恢复模式(targeted recovery mode)，需要在 `data` 目录下创建一个 `recovery.signal` 文件。当归档 WAL 重演完毕或者 `recovery_target` 点到达时，恢复模式结束。

目标恢复模式下需要配置的选项如下:

| 参数配置 | 说明 | 是否必选 |
|:--------|:-----|:--------|
| restore_command = 'cp /path/to/archivedir/%f %p' | 获取归档的 WAL 段文件，这里从 `/path/to/archivedir/` 目录下获取 | 必选 |
| archive_cleanup_command = 'pg_archivecleanup /path/to/archivedir %r' | 清除不再需要的旧的归档 WAL 文件，典型是用于热备情况 | 可选 |
| recovery_end_command = 'rm -rf %r' | 在恢复结束后执行，用于清除接下来的复制与恢复 | 可选 |
