
很多开源库在进行编译时都要求 CMake 有很高的版本，大概 > 3.13 吧。虽然 CMake 的编译安装很简单，但也记录一个安装说明。

具体参考 CMake tarball 解压顶层目录下的 README.rst 文件。

```sh
    ./bootstrap --prefix=/usr/local/cmake
    make
    make install
```

不过还是更建议使用官方提供好的二进制包。

[3.15.0](https://github.com/Kitware/CMake/releases/tag/v3.15.0)
