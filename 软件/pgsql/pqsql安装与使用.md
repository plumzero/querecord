
#### 环境与版本

Debian 8.0

postgresql-13.1

[参考](INSTALL)


#### 目录说明

数据存储目录: `/usr/local/pgsql/data`

软件安装目录: `/usr/local/pgsql`


#### 安装

解压 配置
```sh
    tar -zxvf postgresql-13.1.tar.gz
    cd postgresql-13.1
    ./configure --prefix=/usr/local/pgsql --
```

编译 安装
```sh
    make
    make install
```


#### 启动

为 pgsql 创建用户帐户，后续 pgsql 会通过此用户运行
```sh
    root# adduser postgres
```

创建数据存储目录，并为其设置用户权限
```sh
    root# mkdir /usr/local/pgsql/data
    root# chown postgres /usr/local/pgsql/data
```

在 postgres 账户权限下执行 initdb 命令
```sh
    root# su - postgres
    postgres$ /usr/local/pgsql/bin/initdb -D /usr/local/pgsql/data
```

后台启动 postgres server
```sh
    postgres$ /usr/local/pgsql/bin/pg_ctl -D /usr/local/pgsql/data start
```

后台重启
```sh
    postgres$ /usr/local/pgsql/bin/pg_ctl -D /usr/local/pgsql/data restart
```

如果需要关闭，执行如下命令:
```sh
    postgres$ /usr/local/pgsql/bin/pg_ctl -D /usr/local/pgsql/data stop
```


#### 测试

创建数据库
```sh
    postgres$ /usr/local/pgsql/bin/createdb testdb
```

访问数据库
```sh
    postgres$ /usr/local/pgsql/bin/psql testdb
```
