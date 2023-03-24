
pkg-config 不是一个标准，一些软件会在安装成功时生成一个 pkg-config 目录，该目录下的文件有该软件的相关配置和位置信息。

你可以将此目录添加到 `$PKG_CONFIG_PATH` 搜索路径上，之后可以通过 pkg-config 命令搜索到相关库的信息。
```sh
  pkg-config --libs lua5.3
  pkg-config --cflags lua5.3
```
也可以与 gcc 结合使用:
```sh
  gcc `pkg-config --libs --cflags lua5.3` -o test test.c
```
你也可以编写自己的 pkg-config 文件实现相同操作目的。

其他命令

列出管理的库
```s
  pkg-config --list-all
```

库的版本
```s
  pkg-config --modversion zlib
```
