
一般在构建工程时，要求 CMake 的最小版本为 2.8 即可。但也有一些开源库在进行编译时要求 CMake 有很高的版本(如 3.13)，以适应新需求。

虽然 CMake 的编译安装很简单，但也记录一个安装说明。具体参考 CMake tarball 解压顶层目录下的 README.rst 文件。
```sh
    ./bootstrap --prefix=/usr/local/cmake
    make
    make install
```

不过相对于编译安装，这里还是更建议使用官方提供好的二进制包。
