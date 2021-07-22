
### CREATE DATABASE

创建数据库必须具有超级用户权限。

缺省情况下，新建数据库时从 `template1` 克隆，也可以通过 `TEMPLATE` 指定其他的数据库模板，比如可以从干净的数据库模板 `template0` 上克隆。

语法: 只写几个有用的参数
```sql
    CREATE DATABASE name
        [ 
            [ WITH ]
                [ OWNER [=] user_name ]
                [ TEMPLATE [=] template ]
                [ ENCODING [=] encoding ]
                [ TABLESPACE [=] tablespace_name ]
                [ ALLOW_CONNECTIONS [=] allowconn ]
                [ CONNECTION LIMIT [=] connlimit ]
        ]
```
* `name`: 用来指定要创建的数据库名称。
* `user_name`: 指定新数据库的所属角色，缺省时归属命令执行角色。
* `template`: 指定从哪个模板创建，缺省时为 `template1`。
* `encoding`: 编码方式，如`UTF8`。
* `tablespace_name`: 指定数据库在哪个表空间上创建。
* `allowconn`: 如果为 `false` 时没有谁可以连到这个数据库。缺省为 true。
* `connlimit`: 设置同时可连接到该数据库的最大数量。缺省为 -1，表示无限制。

示例: 一般创建
```sql
    CREATE DATABASE lusiadas;
```

示例: 在表空间 salesspace 上创建一个属主为 salesapp 的数据库:
```sql
    CREATE DATABASE sales
        OWNER salesapp
        TABLESPACE salesspace;
```


### ALTER DATABASE

改变数据库的属性。只有数据库的属主或者超级用户才能执行这个指令。

```sql
    ALTER DATABASE name
        [ [ WITH ] option [ ... ] ]
```
`option` 可以是:
```sql
    ALLOW_CONNECTIONS allowconn
    CONNECTION LIMIT connlimit
```

重命名数据库
```sql
    ALTER DATABASE name RENAME TO new_name
```

改变数据库的属主
```sql
    ALTER DATABASE name OWNER TO { new_owner | CURRENT_USER | SESSION_USER }
```

重新设置数据库的表空间
```sql
    ALTER DATABASE name SET TABLESPACE new_tablespace
```
只有属主或超级用户才能执行，此外还必须具有表空间 new_tablespace 的创建权限。执行这个命令时，会物理地将该数据库中在旧表空间上的所有表或者索引移到新的表空间上。

设置 `postgresql.conf` 中或命令行中指定的运行时参数。注意，某些参数只能通过超级用户设置。
```sql
    ALTER DATABASE name SET configuration_parameter { TO | = } { value | DEFAULT }
```

示例:
```sql
    ALTER DATABASE test SET enable_indexscan TO off;
```


### DROP DATABASE


移除数据库。只能由数据库属主执行。

```sql
    DROP DATABASE [IF EXISTS] name
        [ [ WITH ] ( option [, ...] ) ]
```
`option` 可以是 `FORCE`。

该命令将移除该数据库的目录项并删除该目录下所包含的数据。

当目标库有连接时会删除失败，也可以指定 `FORCE` 强制删除。
