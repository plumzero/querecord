
## C 语言 && 操作系统分类 && POSIX标准
- C 语言变迁
    + K&R -> ANSI C89 -> ISO C99 -> C11
    + 其中 ASNI C89 通常称为 ASNI C。
    + 微软 Visual Studio 的 C++ 编译器目前只提供了与 C89 相容的模式。
    + 支持 for 循环内变量定义是 C99 出现的标准，不过 VS 也支持，太乱了。
- 操作系统分类
    + POSIX 兼容系统家族
    + Windows 操作系统家族
    + 不同操作系统栈空间大小不同。在 windows 下，栈的大小是 2MB。linux 缺省栈空间大小为 8MB
      ，可以通过 ulimit -a 查看，通过 ulimit -s 修改。
- POSIX 标准
    + BSD (Berkeley Software Distribution, 伯克利软件发行版，如 Mac)
        + BSD 许可证(如 clang)
    + GNU (GNU's Not UNIX，如 Linux)
        + GNU 公共许可证(如 gcc)
        + 次级 GPL 许可证(如 Glib)
- Posix for Windows
    + Windows 下使用 POSIX 环境，需要使用 Cygwin 。
    + 如果不需要调用 POSIX 函数，则可以使用 MinGW(Minimalist GUN for Winodws)。 
    + 如果想在 Windows 下使用 Linux 下的一些工具，如 gcc, 可以使用 Win-builds:
        + 版本 Win-builds 1.5.0
        + [Win-builds 1.5.0](http://win-builds.org/doku.php/download_and_installation_from_windows)
        + 傻瓜式配置，说明省略
- 查看一个程序或者动态链接库依赖于哪些库，用下面的命令：
    + Cygwin: cygcheck libxx.dll
    + Linux: ldd libxx.so
    + Mac: otool -L libxx.dylib

## C 开发环境包
- gcc 编译器
- gdb 调试器
- valgrind 用于测试 C 内在使用错误
- gprof 用于运行效率评测
- pkg-config 用于查找库
- doxygen 用于生成程序文档

## gcc 技巧
- 打印机器的预定义宏
  ```shell
    touch test.c
    gcc -E -dM -c test.c
  ```
- 使用 gcc 进行编译时，为了检测栈溢出，可以在编译时启用 -fstack-protector 或 -fstack-protector-all 
  标志，更建议使用后者。

## 其他工具
- 查看中间目标文件的 ELF 符号表 readelf
  ```shell
    readelf -s swap.o
  ```
  可用于查看各符号的各见性。
- 查看某个库的所在路径 locate
  ```shell
    locate libssl.so
  ```
- 显示二进制目标文件的符号表(主要是函数名称) nm
    + 通过此命令对汇编后的目标文件 .o 进行查看。
    + 对于解析 undefined symbol 编译错误(即程序要求调用某个函数，但该函数因为某种原因，未被链
      接到可执行程序中)，nm 命令非常有用。
    + 通过对所有目标文件运行 nm 命令，就可定位缺失的符号是在哪里引用的，在哪里定义的。
      ```shell
        nm obj.o
        nm a.out
      ```
- 提供目标文件的更详细信息 objdump
    + 下面命令可以提供目标文件的扩展信息: 文件的类型、文件所包含的各区段信息(例如程序文本、数
      据、未初始化数据、只读数据等)、这些区段在文件中的位置，以及载入内存后的位置。
      ```shell
        objdump -x main.o
      ```
      这些信息是 file 和 nm 命令所提供信息的超集。
    + 此工具还提供了把机器码反汇编成汇编语言的能力，这一功能相当重要，如果你怀疑汇编器生成的机
      器指令有错，就可以用它进行检查。
      ```shell
        objdump -d a.out        ## 将代码反汇编
        objdump -S a.out        ## 间行输出源代码和反汇编语句
      ```
- 查看二进制文件(但不限于)的十六进制编码 hexdump
  ```shell
    hexdump -e '16/1 "%02X " "\n"' a.out
    hexdump -e '16/1 "%02X " "  |  "' -e '16/1 "%_p" "\n"' en.txt
  ```
- 静态库的创建 ar
    + 静态程序库只是多个目标文件的归档文件(所以也称为归档文件，archive)，可以在需要时链接到可
      执行程序；而动态程序库则是在运行时载入内存，由程序直接调用所需的函数。
    + 负责创建静态程序库归档文件(用 -rs 选项)，还可以检查归档文件的内容(用 -t 选项)
      ```shell
        ar -rs mymyth.a sqrt.o sine.o cosine.o tan.o
        ar -t mymath.a
      ```
- 动态库的创建
    + 在创建目标文件时，要使用位置无关代码(position-independent code, PIC),使之可以在程序需要
      时载入内存的动态位置。
    + 对于可执行程序来说，构造系统所创建的共享程序库，就像是这个可执行程序所独有的程序库，除非
      在创建时使用 -shared 选项，将其创建为动态程序库(后缀名为 .so)。
      ```shell
        gcc -c -fPIC sqrt.c
        gcc -c -fPIC sine.c
        gcc -c -fPIC cosine.c
        gcc -c -fPIC tan.c
        gcc -shared -o libmymath.so sqrt.o sine.o cosine.o tan.o
      ```
  
    + 在生成可执行程序时，尽管你已经用 -L 选项告诉 GCC 这个程序库存放在哪里，但还需要告诉操作系
      统在哪里载入这个程序库。操作系统可以自动搜索 /lib 和 /usr/lib 之类的标准目录，但并不搜索非
      标准位置，所以还必须首先设置 LD_LIBRARY_PATH 环境变量，使之包含这些非标准位置。

- 检测端口服务是否连通 telnet
    + 开启一个网络服务时，需要将对应此服务的端口开放，供客户端连接。
    + 客户端可以通过 telnet 命令测试对端连通性
      ```shell
        telnet 192.168.0.105 peer_port
      ```
      如果出现:
      ```shell
        Trying 192.168.0.105...
        Connected to 192.168.0.105.
        Escape character is '^]'.
      ```
      如果出现
      ```shell
        Trying 192.168.0.105...
        telnet: Unable to connect to remote host: No route to host
      ```
    + 服务其实就是端口的子集，所以也可以通过 curl 或 wget 命令测试端口的连通性。