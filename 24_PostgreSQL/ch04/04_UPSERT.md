
PostgreSQL 的 `UPSERT` 特性是指 INSERT ... ON CONFLICT UPDATE，用来解决在数据插入过程中数据冲突的情况，比如违反用户自定义约束。

在日志数据应用场景中，通常会在事务中批量插入日志数据，如果其中有一条数据违反表上的约束，则整个插入事务将会回滚，PostgreSQL 的 UPSERT 特性能解决这一问题。

```sql
    testdb=> CREATE TABLE user_logins(user_name text primary key,
                login_cnt int4,
                last_login_time timestamp(0) without time zone default now());
    CREATE TABLE
    testdb=> INSERT INTO user_logins(user_name,login_cnt) VALUES ('Jim',1);
    INSERT 0 1
    testdb=> INSERT INTO user_logins(user_name,login_cnt) VALUES ('Tom',1),('Jim',1);
    ERROR:  duplicate key value violates unique constraint "user_logins_pkey"
    DETAIL:  Key (user_name)=(Jim) already exists.
    testdb=> SELECT * FROM user_logins;
    user_name | login_cnt | last_login_time 
    -----------+-----------+-----------------
    Jim       |         1 | 
    (1 row)
```
上述 SQL 试图插入两条数据，不过 Jim 这条数据违反主键冲突，两条数据都不能插入。

PostgreSQL 的 UPSERT 可以处理冲突的数据，比如当插入的数据冲突时不报错，同时更新冲突的数据。
```sql
    testdb=> INSERT INTO user_logins(user_name,login_cnt) VALUES('Tom',1),('Jim',1)
    ON CONFLICT(user_name)
    DO UPDATE SET
    login_cnt=user_logins.login_cnt + EXCLUDED.login_cnt, last_login_time=now();
    INSERT 0 2
    testdb=> select * from user_logins ;
    user_name | login_cnt |   last_login_time   
    -----------+-----------+---------------------
    Tom       |         1 | 2021-09-19 12:40:36
    Jim       |         2 | 2021-09-19 12:40:36
    (2 rows)
```
在产生冲突时，会将 login_cnt 值加 1。ON CONFLICT(user_name) 定义冲突类型为 user_name 字段，DO UPDATE SET 是指冲突动作，后面定义了一个 UPDATE 语句用于处理冲突。
上述 SET 命令中引用了 user_logins 表和内置表 `EXCLUDED`，引用原表 user_logins 访问表中已存在的冲突记录，内置表 EXCLUDED 引用试图插入的值。

这里也可以将 ON CONFLICT(user_name) 后的 DO UPDATE SET ... 语句代替为 `DO NOTHING`，表示什么都不做。
