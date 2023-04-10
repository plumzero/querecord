
apt 的仓库配置文件为 `/etc/apt/sources.list` 。其内容格式如下:
```s
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

```s
  apt-get update
```


### 其他

从源中搜索要下载的软件(可能会出现很多，选择自己需要的种类或版本)，如:

```s
  apt-cache search sshd
```
