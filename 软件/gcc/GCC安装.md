

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

(非并行)编译时长大约 1.5 个小时。

在有些机器上编译时可能还会出现类似于如下的错误:
```
    configure: error: source directory already configured; run "make distclean" there first
    make[1]: *** [configure-mpfr] Error 1
    make[1]: Leaving directory `/usr/local/src/gcc8-build'
    make: *** [all] Error 2
    
    configure: error: source directory already configured; run "make distclean" there first
    make[1]: *** [configure-isl] Error 1
    make[1]: Leaving directory `/usr/local/src/gcc8-build'
    make: *** [all] Error 2
```
这个不妨将 `/usr/local/src/gcc-8.4.0` 中的文件清理一下(如删除 mpfr, isl 等)，或者直接还原回原来的状态，再试一下。

其他错误可以从 config.log 中查看原因分析。


#### 测试

在安装之前，请务必进行测试，GCC 作为底层软件，必须要保证其执行的可靠性。

```shell
    ulimit -s 32768
    make -k test
```
好吧，也可以不用那么严肃。因为一些原因，暂时先不测了。


#### 安装

```shell
    make install
```