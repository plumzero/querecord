
### Posix for Windows

Windows 下使用 POSIX 环境，需要使用 Cygwin 。

如果不需要调用 POSIX 函数，则可以使用 MinGW(Minimalist GUN for Winodws)。 

如果想在 Windows 下使用 Linux 下的一些工具，如 gcc, 可以使用[Win-builds](http://win-builds.org/doku.php/download_and_installation_from_windows)。


### 内容

* [管理构建](ch01)
    * [cmake](ch01/01_cmake)
    * [make](ch01/02_make)
    * [git](ch01/03_git)
    * [pkg-config](ch01/04_pkg-config)
    * [ar](ch01/05_ar)

* [编译调试](ch02)
    * [gcc](ch02/01_gcc)
    * [gdb](ch02/02_gdb)
    * [valgrind](ch02/03_valgrind)

* [程序测试](ch03)
    * [strace](ch03/01_strace)
    * [gcov](ch03/02_gcov)
    * [gprof](ch03/03_gprof)

* [进程访问](ch04)
    * [curl](ch04/01_curl)
    * [telnet](ch04/02_telnet)

* [信息输出](ch05)
    * [nm](ch05/01_nm)
    * [objdump](ch05/02_objdump)
    * [readelf](ch05/03_readelf)
    * [hexdump](ch05/04_hexdump)

* [代码程序](ch06)
    * [Emmet](ch06/01_Emmet)