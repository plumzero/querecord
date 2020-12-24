

[参考](http://www.linuxfromscratch.org/lfs/view/7.9-systemd/chapter06/gcc.html)


#### 配置环境，生成 Make 文件

```shell
    cd /usr/local/src/gcc8-build
    ../gcc-8.4.0/configure --prefix=/usr/local/gcc8 --with-mpc=/usr/local/gcc8-depend/mpc --with-mpfr=/usr/local/gcc8-depend/mpfr --with-isl=/usr/local/gcc8-depend/isl --disable-multilib --enable-checking=release --enable-languages=c,c++ --disable-bootstrap --with-system-zlib
```
这里使用的 zlib 是系统环境上的，而不是 gcc 目录下自带的包，这也是推荐的做法。


#### 编译
```shell
    make
```

make 时报找不到库错误:
```
	/gcc/cc1: error while loading shared libraries: libisl.so.15: cannot open sh
```

解决办法是动态指定库路径编译:
```shell
	LD_LIBRARY_PATH=/usr/local/gcc8-depend/isl/lib make
```


#### 测试

在安装之前，请务必进行测试，GCC 作为底层软件，必须要保证其执行的可靠性。

```shell
    ulimit -s 32768
    make -k test
```


#### 安装