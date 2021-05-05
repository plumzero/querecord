
apt 的仓库配置文件为 `/etc/apt/sources.list` 。其内容格式如下:
```shell
    deb http://mirrors.163.com/debian/ jessie main non-free contrib
    deb http://mirrors.163.com/debian/ jessie-updates main non-free contrib
    deb http://mirrors.163.com/debian/ jessie-backports main non-free contrib
    deb-src http://mirrors.163.com/debian/ jessie main non-free contrib
    deb-src http://mirrors.163.com/debian/ jessie-updates main non-free contrib
    deb-src http://mirrors.163.com/debian/ jessie-backports main non-free contrib
    deb http://mirrors.163.com/debian-security/ jessie/updates main non-free contrib
    deb-src http://mirrors.163.com/debian-security/ jessie/updates main non-free contrib
```


### 更新源
```shell
    apt-get update
```


### 其他
从源中搜索要下载的软件(可能会出现很多，选择自己需要的种类或版本)，如:
```shell
    apt-cache search sshd
```
