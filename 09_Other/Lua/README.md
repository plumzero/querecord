
### 参考

- [Welcome to Lua 5.3](readme.html)
- 版本: lua-5.3.6

### 安装

依赖包安装
- 对于 redhat 系列: `yum install readline-devel`
- 对于 debian 系列: `apt-get install libreadline-dev`

解压 tarball 进入顶层目录下
```sh
    tar -zxvf lua-5.3.6.tar.gz
    cd lua-5.3.6
```

编译、测试与安装
```sh
    make linux; make test; make install
```
顺利的话，会默认安装到 `/usr/local/bin/` 目录下。


### 内容

- 基本概念
    - [值与类型](01_值与类型.md)
    - [metatable和metamethod](02_metatable和metamethod.md)
    - [变量](03_变量.md)
- 语言特性
- 应用接口
- 辅助库 - 函数与类型
- 标准库
