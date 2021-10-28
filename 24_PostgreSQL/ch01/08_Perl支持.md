
pgsql 安装后默认支持的语言可以通过如下方式查看:
```sql
    onedb=> SELECT * FROM pg_language;
      oid  | lanname  | lanowner | lanispl | lanpltrusted | lanplcallfoid | laninline | lanvalidator | lanacl 
    -------+----------+----------+---------+--------------+---------------+-----------+--------------+--------
        12 | internal |       10 | f       | f            |             0 |         0 |         2246 | 
        13 | c        |       10 | f       | f            |             0 |         0 |         2247 | 
        14 | sql      |       10 | f       | t            |             0 |         0 |         2248 | 
     12666 | plpgsql  |       10 | t       | t            |         12663 |     12664 |        12665 | 
    (4 rows)
```

在编写数据库脚本时，可以使用 `plpgsql` 语言进行实现。不过该种语言在读写磁盘文件以及在数据结构支持上不太方便，好在提供了 Perl 扩展。不过这需要我们自己安装，这里根据错误提示进行安装。

操作在 Postgres 用户下进行。

先编写一个 plperl 语言格式的脚本，执行时有报错:
```sql
    ERROR:  language "plperl" does not exist
```

需要执行如下两条语句:
```sql
    CREATE EXTENSION plperl;
    CREATE LANGUAGE plperlu;
```
注意，上面两条语句执行后只对所执行的当前数据库环境有效。比如你当前登录的数据库为 xdb，执行上述两条指令，那么 plperl 仅对 xdb 有效，对其他数据库无效。

执行时报错:
```sql
    ERROR:  could not open extension control file "/usr/local/pgsql/share/extension/plperl.control": No such file or directory
```

好吧，到了这里，其实你要做的工作就是重新进行配置、编译和安装。
