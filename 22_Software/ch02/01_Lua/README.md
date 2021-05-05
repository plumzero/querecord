
### 参考

[Welcome to Lua 5.3](readme.html)

### 安装

- 安装环境

    VMware version:         14.1.1
    linux kernel version:   3.10.0-862.el7.x86_64
    Linux Release:          RedHat 7.5
    Lua version:            lua-5.3.6.tar.gz

- 依赖包安装

  对于 redhat 系列:
  ```sh
    yum install readline-devel
  ```
  
  对于 debian 系列:
  ```sh
    apt-get install libreadline-dev
  ```

- 解压 tarball 进入顶层目录下
  ```sh
    tar -zxvf lua-5.3.6.tar.gz
    cd lua-5.3.6
  ```

- 编译、测试与安装
  ```sh
    make linux
    make test
    make install
  ```
  默认安装到 `/usr/local/bin/` 目录下。
  
  