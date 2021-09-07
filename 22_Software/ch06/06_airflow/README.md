
### 部署环境

* 64-bit machine
* Ubuntu 16.04.7 为主
* 有余力时在 RHEL 7.5 上部署


### 版本说明

* Anaconda3-2021.05-Linux-x86_64.sh
 
  下载地址: https://www.anaconda.com/products/individual-d

* airflow 2.1.3

* PostgreSQL 13.1

  外部数据库。可以部署在同一机器上，也可以部署在其他机器上，但要确保 airflow 可以访问得到。


### 内容

* [编译与部署](01_编译与部署.md)
* [元数据库](02_元数据库.md)
* [多节点部署](03_多节点部署.md)
* [DAG和Operator](04_DAG和Operator.md)
* [配置与生产](05_配置与生产.md)
* [问题与解答](06_问题与解答.md)
* [理解调度系统](07_理解调度系统.md)

### 扩展

* [常用命令](11_常用命令.md)
* [用户与角色](12_用户与角色.md)
