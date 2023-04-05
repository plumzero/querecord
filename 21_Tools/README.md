
*办公室老总让女职员下去买一杯冰淇淋，这合理吗？*

### Posix for Windows

Windows 下使用 POSIX 接口工具，需要使用 Cygwin 。

如果不需要调用 POSIX 函数，则可以使用 MinGW(Minimalist GUN for Winodws)。 

如果想在 Windows 下使用 Linux 下的一些工具，如 gcc, 可以使用[Win-builds](http://win-builds.org/doku.php/download_and_installation_from_windows)。

### 内容

* [管理构建](ch01)
    * [cmake](ch01/01_cmake)
    * [make](ch01/02_make)
    * [meson](ch01/03_meson)
    * [pkg-config](ch01/04_pkg-config)
    * [ar](ch01/05_ar)
    * [git](ch01/06_git)
* [编译调试](ch02)
    * [gcc](ch02/01_gcc)
    * [gdb](ch02/02_gdb)
    * [valgrind](ch02/03_valgrind)
* [测试优化](ch03)
    * [strace](ch03/01_strace)
    * [gcov](ch03/02_gcov)
    * [gprof](ch03/03_gprof)
    * [iperf](ch03/04_iperf)
    * [FlameGraph](ch03/05_flameGraph)
    * [selenium](ch03/06_selenium)
* [信息输出](ch04)
    * [nm](ch04/01_nm)
    * [objdump](ch04/02_objdump)
    * [readelf](ch04/03_readelf)
    * [hexdump](ch04/04_hexdump)
* [其他工具](ch05)
    * [DPDK](ch05/01_dpdk)
    * [wireshark](ch05/02_wireshark)
    * [fcitx](ch05/03_fcitx)
