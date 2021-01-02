
PostgreSQL 可以使用 Perl DBI 模块与 Perl 集成，Perl DBI 模块是 Perl 编程语言的数据库访问模块。 它定义了一组提供标准数据库接口的方法，变量和约定。

一共需要安装两个模块 DBI 和 DBD-Pg，版本如下:
```sh
    DBI-1.637
    DBD-Pg-2.19.3
```

安装方式相同，这里以 DBI-1.637 为示例，假设为 .tar.gz 包:
```sh
    tar -zxvf DBI-1.637.tar.gz
    cd DBI-1.637
    perl Makefile.PL
    make
    make install
```