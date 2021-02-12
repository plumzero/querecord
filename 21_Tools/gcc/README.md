
## 参考
- [GCC镜像站点](https://gcc.gnu.org/mirrors.html)
- [4.8系列](https://gcc.gnu.org/gcc-4.8/)

## 关于 VLA 特性
- 4.8 系列的 g++ 并不支持 VLA 特性；
- 也不建议在程序中使用 VLA 特性，无论编译器支持与否。

## 生产选项
- -Wall
    + 打开所有警告。它是编译程序时的必选项，修正编译时产生的警告，是增强程序健壮性的重要一步。
- -Wconversion
    + 对于可能改变一个值的隐式转换进行警告。
    + 比如实数与整数之间:
      ```c
        double x = 1.1;
        abs(x);         // Warn
        abs((int)x);    // No Warn 
      ```
      比如有符号与无符号数之间:
      ```c
        unsigned ui = -1;           // Warn
        unsigned ui = (unsigned)-1; // No Warn
      ```
      到更小类型的转换:
      ```c
        double x = sqrt(3.1415);    // Warn
      ```
- -Wextra
    + 开启 -Wall 没有打开的警告
    + 此选项过去也叫 -W
- -Werror
    + 把警告当作错误来处理。引用第三方源文件编译时不建议打开。
- -Wmissing-field-initializers
    + 结构体初始化时，如果有成员未进行初始化，则报警。
      ```c
        struct s { int f, g, h; };
        struct s x = { 3, 4 };      // Warn x.h未初始化
      ```
      但如果以下面方法初始化时，就不报警:
      ```c
        struct s { int f, g, h; };
        struct s x = { .f = 3, .g = 4 };    // No Warn
      ```
    + 该报警包含在 -Wextra 中，如果想要开启 -Wextra 但又想忽略这个报警，就使用
      **-Wextra -Wno-missing-field-initializers**
    + 更常使用 -Wextra -Wno-missing-field-initializers
- -Wsign-compare
    + 如果涉及到有符号与无符号类型之间的比较，则报警；
    + 此选项包含在 -W 中。
- -Wignored-qualifiers
    + 如果函数返回值有 const 限定符，则报警；
    + 仅适用于 c/c++ 中。
- -Wtype-limits
    + 如果对非常量比较表达式的结果总是 true 或 false，则报警:
      ```c
        unsigned ui;
        // deal with ui
        if (ui > 0) { /** ... */ }  // Warn 因为 ui 总是大于 0
      ```
    + 此选项包含在 -W 中。
    
## 动态库相关
- -fPIC -shared
    + 生成动态库时，两个经常一起使用
- -Wl,-soname,libv2x.so
    + 指定要生成的动态库名称
- -Wl,-rpath=../openssl/lib:../common/libcurl/lib
    + 编译生成动态库时，如果要生成的动态库还依赖其他动态库，需要在编译时指定依赖库路径
- -Wl,--version-script=control.map
    + 运行时指定多个库时，如果不同的库有相同的全局符号介入，可能会引起符号冲突，可以通过
      该选项控制符号的导出，control.map 文件内容如下:
      ```shell
        {
        global:
          func_1;
          func_2;
        local: *;
        };
      ```
      global表示要导出的符号，local表示不导出的,\*表示都不导出

## 调试选项
- -fprofile-arcs
    + 程序执行期间，记录每个分支或函数调用被执行的次数以及执行时间。
    + 程序执行完毕后，执行结果会保存到 .gcda 文件中，每个源文件都会生成一份这样
      的文件。 
- -ftest-coverage
    + 用于执行覆盖分析测试，通常与 -fprofile-arcs 一起使用。
- -fstack-protector-all 
    + 缓冲区溢出保护
- -Wfloat-equal
    + 如果对浮点类型进行 = 比较，则报警。

## 调优选项
- 调优，也应该算作调试的一部分。
- -fno-elide-constructors
    + c++ 标准允许对创建的临时值进行优化(返回值优化);
    + 此选项可以关闭返回值优化，这样的话 g++ 编译时就会直接调用拷贝构造
- -Wunused
    + 对于只定义却没有使用的变量进行报警，常和 -W 一起使用。
- -Wshadow
    + 如果局部变量或类型声明屏蔽了其他的变量、参数，类型或类成员，或者是内建函数
      被隐藏了，就报警。
- -Winline
    + 如果一个函数进行了 inline 声明，但在编译时却无法内联，则报警。
- -Wmissing-prototypes
    + 如果全局函数没有进行前向类型声明(如头文件中没有包含此全局函数的声明)，则报警。
    + 只在 c 和 objective-c 中使用。
- -Wmissing-declarations
    + 如果全局函数没有进行前向声明(如头文件中没有包含此全局函数的声明)，则报警。
    + 常在 c++ 中使用。
- -Wlong-long
    + 如果使用 long long 类型，则报警；
    + 不会使用这种选项。

## 功能选项
- -Wl,-rpath=/path/to/so
    + 编译时指定动态链接库的位置
    + 示例
      ```make
        $(CXX) $(CXXFLAGS) $(CERTCLI_SRCS)         \
            $(FILEUNZIP_SRCS)                      \
            -o $(CERTCLI_PROJ)                     \
            -I. ./libcertmgr.a                     \
            $(CURL_SUPPORT)                        \
            $(ASN1C_SUPPORT)                       \
            $(THREAD_SUPPORT)                      \
            $(UNZIP_SUPPORT)                       \
            $(OPENSSL_SUPPORT)                     \
            $(SDFILE_SUPPORT)                      \
            $(TORTELLINI_SUPPORT)                  \
            -Wl,-rpath=../common/openssl/lib:../common/sdfile
      ```