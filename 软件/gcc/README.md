
#### 版本与安装环境
```
    Debian 7.5
    gcc-8.4.0
```


#### 解压后下载依赖包

解压
```shell
    tar -zxvf gcc-8.4.0.tar.gz
```

在顶层目录下执行，下载依赖包
```shell
    ./contrib/download_prerequisites
```
执行后，会下载 4 个依赖包:
```
    gmp-6.1.0.tar.bz2
    mpfr-3.1.4.tar.bz2
    mpc-1.0.3.tar.gz
    isl-0.18.tar.bz2
```


#### 创建一些目录

用作安装目录
```shell
    mkdir /usr/local/gcc84
```

用作依赖包安装
```shell
    mkdir /usr/local/gcc84-depend
```

用作 build 目录
```shell
    mkdir /usr/local/src/gcc84-build
```


#### 依赖包安装

gmp-6.1.0.tar.bz2 安装
```shell
    ## 解压 配置 编译
    tar -jxvf gmp-6.1.0.tar.bz2
    cd gmp-6.1.0
    ./configure --prefix=/usr/local/gcc84-depend/gmp CC="gcc -std=c11"
    make
    
    ## 优化
    cd tune
    make speed
    
    ## 安装
    cd ..
    make install
```

mpfr-3.1.4.tar.bz2 安装(依赖包 gmp)
```shell
    ## 解压
    tar -jxvf mpfr-3.1.4.tar.bz2
    cd mpfr-3.1.4
    
    ## 下载补丁并更新
    wget http://www.mpfr.org/mpfr-3.1.4/allpatches
    patch -N -Z -p1 < allpatches
    
    ## 配置  编译
    ./configure --prefix=/usr/local/gcc84-depend/mpfr --with-gmp=/usr/local/gcc84-depend/gmp CC="gcc -std=c11"
    make

    ## 优化
    cd tune
    make -i speed
    
    ## 检验
    cd ..
    make check
    
    ## 安装
    make install
```

mpc-1.0.3.tar.gz 安装(依赖包 gmp mpfr)
```shell
    ## 解压 配置 编译
    tar -zxvf mpc-1.0.3.tar.gz
    cd mpc-1.0.3
    ./configure --prefix=/usr/local/gcc84-depend/mpc --with-gmp=/usr/local/gcc84-depend/gmp --with-mpfr=/usr/local/gcc84-depend/mpfr CC="gcc -std=c11"
    make
    
    ## 检测 安装
    make check
    make install
```

isl-0.18.tar.bz2 安装(依赖包 gmp)
```shell
    ## 解压 配置 编译
    tar -jxvf isl-0.18.tar.bz2
    cd isl-0.18
    ./configure --prefix=/usr/local/gcc84-depend/isl --with-gmp-prefix=/usr/local/gcc84-depend/gmp CC="gcc -std=c11"
    make
    
    ## 安装
    make install
```

#### GCC 编译安装

生成 Make 文件
```shell
    cd /usr/local/src/gcc84-build
    ../gcc-8.4.0/configure --prefix=/usr/local/gcc84 --with-gmp=/usr/local/gcc84-depend/gmp --with-mpc=/usr/local/gcc84-depend/mpc --with-mpfr=/usr/local/gcc84-depend/mpfr --with-isl=/usr/local/gcc84-depend/isl --disable-multilib --enable-checking=release --enable-languages=c,c++ --disable-bootstrap
```

编译 安装
```shell
    make
    make install
```