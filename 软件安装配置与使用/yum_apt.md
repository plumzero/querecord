

## 说明
- 相对来说， yum 源的配置比 apt-get 源更麻烦一些

# yum

## yum 的配置文件
    /etc/yum.conf

## 关于 $basearch 和 $releasever
- 通过 yum 配置文件 yum.conf 的 cachedir 选项
  ```shell
    cachedir=/var/cache/yum/$basearch/$releasever
  ```
- 通过实际查找目录发现
  ```shell  
    $basearch = x86_64
    $releasever = 6
  ```

## 源的更新
RedHat 和 Centos 使用同一个源，均使用 Centos 的源，源可以从多个镜像网站获取，这里从 163 镜像
和 RedHat 为例。
- 卸载 yum && subscription-manager && rhn    Centos 可以只卸载 yum
  ```shell
    rpm -qa | grep yum | xargs rpm -e --nodeps
    rpm -qa | grep subscription-manager | xargs rpm -e --nodeps
    rpm -qa | grep rhn | xargs rpm -e --nodeps
  ```
- 重新安装 yum 包
  ```shell
    rpm -ivh yum-metadata-parser-1.1.4-10.el7.x86_64.rpm 
    rpm -ivh yum-3.4.3-158.el7.centos.noarch.rpm 
    rpm -ivh yum-plugin-fastestmirror-1.1.31-45.el7.noarch.rpm
  ```
- 修改 .repo 文件
  打开[http://mirrors.163.com/](镜像网站)
   阅读[http://mirrors.163.com/.help/centos.html](帮助), 下载 .repo 文件，这里是 
   CentOS7-Base-163.repo，名称随意。
   根据镜像网站中相关 rpm 目录，修改 .repo 文件，这里如下:
   ```shell
    [base]
    name=CentOS-$releasever - Base - 163.com                         // 随便写
    baseurl=http://mirrors.163.com/centos/7.5.1804/os/$basearch/     // 指明了 repositry 的地址，支持ftp,http,file协议
    gpgcheck=1                                                       // 为 1 是会启用下面的 gpgkey
    gpgkey=http://mirrors.163.com/centos/7.5.1804/os/x86_64/RPM-GPG-KEY-CentOS-7
    [updates]
    name=CentOS-$releasever - Updates - 163.com
    baseurl=http://mirrors.163.com/centos/7.5.1804/updates/$basearch/
    gpgcheck=1
    gpgkey=http://mirrors.163.com/centos/7.5.1804/os/x86_64/RPM-GPG-KEY-CentOS-7
    [extras]
    name=CentOS-$releasever - Extras - 163.com
    baseurl=http://mirrors.163.com/centos/7.5.1804/extras/$basearch/
    gpgcheck=1
    gpgkey=http://mirrors.163.com/centos/7.5.1804/os/x86_64/RPM-GPG-KEY-CentOS-7
    [centosplus]
    name=CentOS-$releasever - Plus - 163.com
    baseurl=http://mirrors.163.com/centos/7.5.1804/centosplus/$basearch/
    gpgcheck=1
    enabled=0                                                        // 为 0 时表示 repositry 不可被获取
    gpgkey=http://mirrors.163.com/centos/7.5.1804/os/x86_64/RPM-GPG-KEY-CentOS-7
   ```
- 放置 .repo 文件
  ```shell
   cd /etc/yum.repos.d/
  ```
  对此目录下文件备份
  将前面设置好的 .repo 文件放在此目录下
- 更新源
  ```shell
    yum clean all
  ```
  根据提示执行:
  ```shell
    rm -rf /var/cache/yum
  ```
  更新源:
  ```shell
    yum makecache        // 如果出错根据错误提示修改 .repo 文件
  ```

## 其他
+ 官网的 centos 源，设置方式相同
  ```shell
    http://mirror.centos.org/centos/
  ```
+ 163 的 repo 文件不可用，请使用本目录中 '配置文件参考' 目录下的 repo 文件

## 需要注意
- 如果使用外部的 CentOS 源(比如163镜像源)，其源地址会随 Linux 发行版本更新而改变地址，所以
  在某个时刻执行
  ```shell
    yum install xxx_package
  ```
  时可能会发现，安装不了了。这是因为地址更新了。
- 比如 [base] 选项中的 baseurl 之前是:
  ```shell
    baseurl=http://mirrors.163.com/centos/7.5.1804/os/$basearch/
  ```
  随着 Linux 发行版本的更新，原来的 baseurl 失效，新的变成是:
  ```shell
    baseurl=http://mirrors.163.com/centos/7.7.1908/os/$basearch/
  ```
  以后可能还会变。
- 所以在每次 yum makecache 时，如果失败的话，很可能是这个原因。
  具体应该改成哪个 url, 需要查看[http://mirrors.163.com/](163开源镜像站)。

# apt-get

## 源list
```shell
    /etc/apt/sources.list
```
## 将下列内容写入 源list 中
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
## 更新源
```shell
    apt-get update
```
## 其他
- 从源中搜索要下载的软件(可能会出现很多，选择自己需要的种类或版本)，如:
  ```shell
    apt-cache search sshd
  ```

  