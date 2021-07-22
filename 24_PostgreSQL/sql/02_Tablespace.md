
### CREATE TABLESPACE

定义表空间。

只有超级用户可以定义表空间，但可以将这个表空间分配给其他角色使用。

```sql
    CREATE TABLESPACE tablespace_name
        [ OWNER { new_owner | CURRENT_USER | SESSION_USER } ]
        LOCATION 'directory'
        [ WITH ( tablespace_option = value [, ... ] ) ]
```
`directory` 指定用于创建表空间的绝对目录路径，必须事先被创建且目录为空，且为数据库超级用户所有。

新定义的表空间不得与已存在的表空间重复，且不得以 `pg_` 开头。


示例: 创建表空间目录并设置为超级用户所有
```sh
    mkdir /data/dbs
    chown postgres:postgres /data/dbs
```

示例: 创建表空间
```sql
    CREATE TABLESPACE dbspace LOCATION '/data/dbs';
```

示例: 创建一个为 genevieve 角色所拥有的表空间
```sql
    CREATE TABLESPACE indexspace OWNER genevieve LOCATION '/data/indexes';
```


### ALTER TABLESPACE

改变表空间的定义。

重命名表空间，不得以 `pg_` 开头
```sql
    ALTER TABLESPACE name RENAME TO new_name
```

重定义表空间的属主
```sql
    ALTER TABLESPACE name OWNER TO { new_owner | CURRENT_USER | SESSION_USER }
```


### DROP TABLESPACE

移除表空间。

```sql
    DROP TABLESPACE [ IF EXISTS ] name
````
在移除之前，必须保证该表空间中所有的数据库对象为空。
