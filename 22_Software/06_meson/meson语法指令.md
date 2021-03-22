
语法: <strong> meson [command] [arguments] [options] </strong>

[more information](https://mesonbuild.com/Commands.html)


#### meson setup

指定编译目录 builddir
```
    meson setup builddir
```

指定编译目录 builddir 和源文件目录 srcdir
```
    meson setup builddir srcdir
```

缺省情况下，meson 创建的是一个 `debug` 工程环境，可以通过 `--buildtype` 选项指定修改:
```
    meson setup builddir --buildtype=release
```

缺少情况下，编译器为 GCC 系列。这样指定修改:
```
    CC=clang CXX=clang++ meson setup builddir
```

更多该指令用法可通过 `meson setup --help` 查看。


#### meson compile

```
    meson compile -C builddir
```
本质上还是使用 `ninja` 的编译系统来执行的。

使用 `ninja` 比 `make` 要快，是因为前者可以自动推导出 CPU 核数并在此基础上并行编译。


#### meson test

执行测试:
```
    meson test -C builddir
```
等同于:
```
    ninja -C builddir test
```


#### meson install

缺省情况下会安装到 `/usr/local` 目录下:
```
    meson install -C builddir
```

也可以通过设置环境变量的方式指定安装目录:
```
    DESTDIR=/path/to/install meson install -C builddir
```
测试暂时没成功。

