
#### 环境与版本

Debian 8.0

postgresql-13.1

[参考](INSTALL)


#### 目录说明

数据存储目录: `/usr/local/pgsql/data`

软件安装目录: `/usr/local/pgsql`


#### 依赖
```
	apt-get install libreadline-dev
```


#### 安装

解压 配置
```sh
    tar -zxvf postgresql-13.1.tar.gz
    cd postgresql-13.1
    ./configure --prefix=/usr/local/pgsql
```

编译 安装
```sh
    make
    make install
```


#### 启动

创建系统用户组和用户:
```sh
    root# adduser postgres
    root# id postgres
    uid=1012(postgres) gid=1012(postgres) groups=1012(postgres)
```

创建相关目录，修改目录属主，并修改数据目录的权限为 0700:
```sh
    root# mkdir -p /pgdata/10/{data,backups,scripts,archive_wals}
    root# chown -R postgres.postgres /pgdata/10
    root# chmod 0700 /pgdata/10/data
```

在 postgres 账户权限下执行 initdb 命令(为超级用户 postgres 设置一个密码):
```sh
    root# su - postgres
    postgres$ /usr/local/pgsql/bin/initdb -D /pgdata/10/data -W
```

后台启动 postgres server
```sh
    postgres$ /usr/local/pgsql/bin/pg_ctl -D /pgdata/10/data -l /pgdata/10/data/logfile start
```

后台重启
```sh
    postgres$ /usr/local/pgsql/bin/pg_ctl -D /pgdata/10/data -l /pgdata/10/data/logfile restart
```

如果需要关闭，执行如下命令:
```sh
    postgres$ /usr/local/pgsql/bin/pg_ctl -D /pgdata/10/data -l /pgdata/10/data/logfile stop
```


#### 测试

人工在 pqsql 操作台输入 sql 语句进行测试。

创建数据库
```sh
    postgres$ /usr/local/pgsql/bin/createdb testdb
```

访问数据库
```sh
    postgres$ /usr/local/pgsql/bin/psql testdb
```
执行完之后会进入 pqsql 操作台，如下:
```sh
    testdb=# 
```

建表操作:
```sh
    testdb=# create table myfirst(id INT PRIMARY KEY NOT NULL, name TEXT NOT NULL);
    CREATE TABLE
```

插入操作:
```sh   
    testdb=# insert into myfirst(id,name) values (1, 'Paul'),(2,'Allen');
    INSERT 0 2
```

读取操作:
```sh   
    testdb=# select * from myfirst;
     id | name  
    ----+-------
      1 | Paul
      2 | Allen
    (2 rows)
```

