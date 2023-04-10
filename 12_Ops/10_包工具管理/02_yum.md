
### yum 的配置文件 /etc/yum.conf 详解

`/etc/yum.conf` 文件是 yum 主配置文件。其内容格式如下:
```s
  [main]
  // 使用 yum 下载 rpm 软件包的缓存目录
  cachedir=/var/cache/yum/$basearch/$releasever
  // 缓存是否需要保存，1 表示保存，0 表示不保存
  keepcache=0
  // 调试级别(0-10)，默认为 2
  debuglevel=2
  // yum 日志文件名称
  logfile=/var/log/yum.log
  // 是否只升级和安装软件包的 CPU 体系一致的包，如果设为 1, 那么如果安装了一个
  //   i386 的 rpm, 则 yum 不会用 i686 的包来升级
  exactarch=1
  // 是否允许更新陈旧的 rpm 软件包，1 表示允许，0 表示不允许
  obsoletes=1
  // 是否执行 GPG 签名检查，1 表示执行检查，0 表示不执行检查
  gpgcheck=1
  // 是否允许使用插件，1 表示允许，0 表示不允许
  plugins=1
  // 允许保留多少个内核包
  installonly_limit=3
```
该配置文件一般很少改动。


### yum 软件仓库配置文件

软件仓库配置文件默认存储在 `/etc/yum.repos.d` 目录中，以 .repo 文件命名。

一个 repo 文件可以定义一个或者多个软件仓库的细节内容，.repo 文件中的设置内容将被 yum 读取和应用。

yum 软件仓库配置文件的格式内容如下:
```s
  // 方括号里面的是软件源的名称，会被 yum 识别
  [rhel-source]
  // name 定义了软件仓库的名称，通常是为了方便阅读配置文件， $releasever 变量定义了发行版本，
  //  $basearch 变量定义了系统的架构，可以是 i386、x86_64 等值，这两个变量根据当前系统的版本
  //  架构不同而有不同的取值，可以方便 yum 升级的时候选择适合当前系统的软件包
  name=Red Hat Enterprise Linux $releasver - $basearch - Source
  // 指定 rpm 软件包来源，支持的协议有 http://, ftp:// 以及 file:// 这三种
  baseurl=ftp://ftp.redhat.com/pub/redhat/linux/enterprise/$releasever/en/os/SRPMS/
  // 表示软件仓库中定义的源是否启用， 0 表示禁用， 1 表示启用
  enabled=1
  // 表示这个软件仓库中下载的 rpm 软件包将进行 GPG 校验，以确定该软件包的来源是否有效和安全
  gpgcheck=1
  // 定义用于校验的 GPG 密钥
  gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-redhat-release
```


### 关于 $basearch 和 $releasever

通过 yum 配置文件 yum.conf 的 cachedir 选项
```s
  cachedir=/var/cache/yum/$basearch/$releasever
```

通过实际查找目录发现
```s  
  $basearch = x86_64
  $releasever = 6
```


### 源的更新操作

RedHat 和 Centos 使用同一个源，均使用 [Centos源](http://mirror.centos.org/centos/)。源可以从多个镜像网站获取，这里以从 163 镜像和 RedHat 为例。

RedHat 需要对注册进行破解，所以需要删除原有 yum 以跳过注册机制。本目录也保存了适用于 RHEL7.5 的[注册破解包](rhel7.5)。

1. 更新 yum 。 
  
   卸载 yum && subscription-manager && rhn    Centos 可以只卸载 yum
   ```s
    rpm -qa | grep yum | xargs rpm -e --nodeps
    rpm -qa | grep subscription-manager | xargs rpm -e --nodeps
    rpm -qa | grep rhn | xargs rpm -e --nodeps
   ```

   重新安装 yum 包
   ```s
    rpm -ivh yum-metadata-parser-1.1.4-10.el7.x86_64.rpm 
    rpm -ivh yum-3.4.3-158.el7.centos.noarch.rpm 
    rpm -ivh yum-plugin-fastestmirror-1.1.31-45.el7.noarch.rpm
   ```

2. 修改 .repo 文件。

   打开[镜像网站](http://mirrors.163.com/)，阅读[帮助](http://mirrors.163.com/.help/centos.html), 下载 .repo 文件，这里是 CentOS7-Base-163.repo，名称随意。
   
   根据镜像网站中相关 rpm 目录，修改 .repo 文件，这里如下:
   ```s
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

3. 放置 .repo 文件。
   ```s
    cd /etc/yum.repos.d/
   ```
  对此目录下文件备份。并将前面设置好的 .repo 文件放在此目录下

4. 更新源。
   ```s
    yum clean all
   ```
   根据提示执行:
   ```s
    rm -rf /var/cache/yum
   ```
   更新源:
   ```s
    yum makecache        // 如果出错根据错误提示修改 .repo 文件
   ```


### 需要注意

如果使用外部的 CentOS 源(比如163镜像源)，其源地址会随 Linux 发行版本更新而改变地址，所以在某个时刻执行 `yum install xxx_package` 时可能会发现，安装不了了，这很可能是因为地址更新了。

比如 [base] 选项中的 baseurl 之前是:
```s
  baseurl=http://mirrors.163.com/centos/7.5.1804/os/$basearch/
```
随着 Linux 发行版本的更新，原来的 baseurl 失效，新的变成是:
```s
  baseurl=http://mirrors.163.com/centos/7.7.1908/os/$basearch/
```

所以在每次 `yum makecache` 时，如果失败的话，很可能是这个原因。具体应该改成哪个 url, 需要查看[163开源镜像站](http://mirrors.163.com/)。
