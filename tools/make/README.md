
### 参考
- [Makefile 使用总结](https://www.cnblogs.com/wang_yb/p/3990952.html)
- [跟我一起写Makefile:MakeFile介绍](https://wiki.ubuntu.org.cn/跟我一起写Makefile:MakeFile介绍)
- [Shell脚本——make命令和Makefile文件](https://blog.csdn.net/twc829/article/details/72729799)
    
### 简介
- 基本格式
  ```make
    target ... : prerequisites ...
        command
        ...
        ...
  ```
  其中:
  ```shell
    target              目标文件，可以是 object file，也可以是可执行文件
    prerequisites       生成 target 所需要的文件或者目标
    command             make 需要执行的命令(任意的 shell 命令)， Makefile 中的命令必须以 [tab] 开头
  ```
    + target 是必须的； prerequisites 和 command 是可选的，但两者必须至少存在一个。
    + target 可以是文件名，即构建对象；也可以是操作的名称，即伪目标。
    + prerequisites 不存在或只要有一个 prerequisites 有更新，则 target 需重新构建。
- 组成部分
    + 显式规则: 说明如何生成一个或多个目标文件（包括 生成的文件，文件的依赖文件，生成的命令）
    + 隐晦规则: make 的自动推导功能所执行的规则
    + 变量定义: Makefile 中定义的变量
    + 文件指示: Makefile 中引用其他 Makefile; 指定 Makefile 中有效部分；定义一个多行命令
    + 注释:       Makefile 只有行注释"#"，如果要使用或者输出"#"字符，需要进行转义，"\#"
- GNU make 的工作流程
    + 读入主 Makefile(主 Makefile 中可以引用其他 Makefile)
    + 读入被 include 的其他 Makefile
    + 初始化文件中的变量
    + 推导隐晦规则，并分析所有规则
    + 为所有的目标文件创建依赖关系链
    + 根据依赖关系，决定哪些目标要重新生成
    + 执行生成命令

### 初级语法
- 规则
    + 语法
        + 规则主要由两部分组成：依赖关系和生成目标的方法
        + 规则格式有两种写法:
          ```make
            target ... : prerequisites ...
                command
                ...
          ```
          或者
          ```make
            target ... : prerequisites ; command
                command
                ...
          ```
    + 通配符
      ```shell
          *         表示任意一个或多个字符
          ?         表示任意一个字符
          [...]     示例 [abcd] 表示 a,b,c,d 中任意一个字符，[^abcd] 表示除 a,b,c,d 以外的字符，[0-9] 表示 0~9 中任意一个数字
          ~         表示用户的 home 目录
      ```
    + 路径搜索
        + 当一个 Makefile 中涉及到大量源文件时(这些源文件和 Makefile 极有可能不在同一个目录中)，
          这时，最好将源文件的路径明确在 Makefile 中，便于编译时查找。
        + Makefile 中的特殊变量 VPATH 就是完成上述功能的。
        + 指定了 VPATH 之后，如果当前目录中没有找到相应文件或依赖的文件，Makefile 会到 VPATH 指
          定的路径中再去查找。
        + VPATH 使用方法:
          ```shell
            vpath <directories>             :: 当前目录中找不到文件时，就从 <directories> 中搜索
            vpath <pattern><directories>        :: 符合 <pattern> 格式的文件，就从 <directories> 中搜索
            vpath <pattern>                 :: 清除符合 <pattern> 格式的文件搜索路径
            vpath                               :: 清除所有已经设置好的文件路径
          ```
        + 示例1 - 当前目录中找不到文件时, 按顺序从 src目录 ../parent-dir目录中查找文件
          ```make
            VPATH src:../parent-dir   
          ```
        + 示例2 - .h结尾的文件都从 ./header 目录中查找
          ```make
            VPATH %.h ./header
          ```
        + 示例3 - 清除示例2中设置的规则
          ```make
            VPATH %.h
          ```
        + 示例4 - 清除所有VPATH的设置
          ```make
            VPATH
          ```
- 变量
    + 变量定义
        + = 和 :=            := 只能使用前面定义好的变量，= 可以使用后面定义的变量
        + 参考 makefile_define
    + 变量替换
        + 参考 makefile_replace
    + 变量的追加
        + 参考 makefile_append
    + 变量的覆盖
        + 作用是使 Makefile 中定义的变量能够覆盖 make 命令参数中指定的变量
        + 语法：
          ```make
            override <variable> =  <value>
            override <variable> := <value>
            override <variable> += <value>
          ```
        + 参考 makefile_override
    + 目标变量
        + 作用是使变量的作用域仅限于这个目标(target)，而不像之前例子中定义的变量，对整个 Makefile 都有效。
        + 语法:
          ```make
            <target ...> :: <variable-assignment>
            <target ...> :: override <variable-assignment>
          ```
        + 参考 makefile_target
- 命令前缀
    + Makefile 中书写 shell 命令时可以加 2 种前缀 @ 和 -, 或者不用前缀。
    + 3 种格式的 shell 命令区别如下：
        + 不用前缀: 输出执行的命令以及命令执行的结果，出错的话停止执行
        + 前缀 @: 只输出命令执行的结果，出错的话停止执行（关闭回显）
        + 前缀 -: 命令执行有错的话，忽略错误，继续执行
    + 参考 makefile_prefix
- 伪目标
    + 伪目标并不是一个 "目标(target)"，不像真正的目标那样会生成一个目标文件。
    + 典型的伪目标文件是 Makefile 中用来清理编译过程中中间文件的 clean 伪目标，一般格式如下:
      ```make
        .PHONY: clean
        clean:
            -rm -f *.o
      ```
- 引用其他的 Makefile
    + 语法: include <filename>    (filename 可以包含通配符和路径)
    + 参考 makefile_quote
- make 退出码
    + Makefile 的退出码有 3 种：
        + 0 成功执行
        + 1 make 命令出现了错误
        + 2 使用了 "-q" 选项，并且 make 使得一些目标不需要更新
- 指定 Makefile，指定特定目标
    + 默认执行 make 命令时， GNU make 在当前目录下依次搜索下面 3 个文件 "GNUmakefile", "makefile", "Makefile"。 
    + 找到对应文件之后，就开始执行此文件中的第一个目标(target)，如果找不到这 3 个文件就报错。
    + 非默认情况下，可以在 make 命令中通过 -f 指定特定的 Makefile 和特定的目标。
      ```shell
        make -f makefile_target target2
      ```
- make 参数介绍
    + 通过 make -h 去查看
      ```shell
        参数                          含义
        --debug[=<options>]         输出 make 的调试信息，options 可以是 a, b, v
        -j --jobs                   同时运行的命令的个数，也就是多线程运行 Makefile
        -r --no-builtin-rules       禁止使用任何隐含规则
        -R --no-builtin-variables   禁止使用任何作用于变量上的隐含规则
        -B --always-make            假设所有目标都有更新，即强制重编译
      ```
- Makefile 隐含规则
    + 编译 C 时，<n>.o 的目标会自动推导为 <n>.c
    + 编译 CPP 时，<n>.o 的目标会自动推导为 <n>.cpp
    + 参考 makefile_implication
   
- 隐含规则中的 命令变量 和 命令参数变量
    + 命令变量
      ```shell
        变量名         含义
        RM              rm -f
        AR              ar
        CC              cc
        CXX             g++
      ```
      参考 makefile_cmdvar
    + 命令参数变量
      ```shell
        变量名         含义
        ARFLAGS         AR 命令的参数
        CFLAGS          C语言编译器的参数
        CXXFLAGS        C++语言编译器的参数
      ```
    + 自动变量
      Makefile 中很多时候通过自动变量来简化书写 依赖目标是 prerequisites
      ```shell
        自动变量        含义
        $@              目标集合
        $%              当目标是函数库文件时，表示其中的目标文件名
        $<              第一个依赖目标。如果依赖目标是多个，逐个表示依赖目标
        $?              比目标新的依赖目标的集合
        $^              所有依赖目标的集合，会去除重复的依赖目标
        $+              所有依赖目标的集合，不会去除重复的依赖目标
        $*              这个是 GNU make 特有的，其它的 make 不一定支持
      ```

### 高级语法
- 嵌套 Makefile
    + 向引用的其它 Makefile 传递参数
    + 语法：
      ```make
        export variable  = value
        export variable := value
        export variable += value
      ```
    + 参考 makefile_passpara
- 定义命令包
    + 命令包将连续相同的命令合成一条，减少 Makefile 的代码量。
    + 语法:
      ```make
        define <command-name>
        command
        ...
        endef
      ```
    + 参考 makefile_cmdpkg
- 条件判断
    + 条件判断的关键字主要有  ifeq ifneq ifdef ifndef
    + 语法:
      ```make
        <conditional-directive>
        <text-if-true>
        endif
      ```
      或者
      ```make
        <conditional-directive>
        <text-if-true>
        else
        <text-if-false>
        endif
      ```
    + 参考 makefile_if
- Makefile 中的函数
    + 函数调用语法
      ```make
        $(<function> <arguments>)
      ```
      或者
      ```make
        ${<function> <arguments>}
          <function>    函数名
          <arguments>   函数参数
      ```
    + 字符串函数
        + 字符串替换函数
          ```shell
            $(subst<from>,<to>,<text>)
            功能：把字符串 <text> 中的 <from> 替换为 <to>
            返回：替换过的字符串
          ```
          参考 makefile_str_subst
        + 模式字符串替换函数
          ```shell
            $(patsubst <pattern>,<replacement>,<text>)
            功能：查找 <text> 中的单词（单词以"空格","tab","换行"来分割）是否符合 <pattern>，
                  符合的话，用 <replacement> 替代。
            返回：替换过的字符串。
          ```
          + 参考 makefile_str_patsubst
        + 去空格函数
          ```shell
            $(strip <string>)
            功能：去掉 <string> 字符串中开头和结尾的空字符
            返回：被去掉空格的字符串值
          ```
          参考 makefile_str_strip
        + 查找字符串函数
          ```shell
            $(findstring <find>,<in>)
            功能：在字符串 <in> 中查找 <find> 字符串
            返回：如果找到，返回 <find> 字符串，否则返回空字符串
          ```
          参考 makefile_str_findstring
        + 过滤函数
          ```shell
            $(filter <pattern...>,<text>)
            功能：以 <pattern> 模式过滤字符串 <text>, 保留符合模式 <pattern> 的单词，可以有多个模式
            返回：符合模式 <pattern> 的字符串
          ```
          参考 makefile_str_filter
        + 反过滤函数
          ```shell
            $(filter-out <pattern...>,<text>)`
            功能：以 <pattern> 模式过滤字符串 <text>，去除符合模式 <pattern> 的单词，可以有多个模式
            返回：不符合模式 <pattern> 的字符串
          ```
          参考 makefile_str_filterout
        + 排序函数
          ```shell
            $(sort <list>)
            功能：给字符串 <list> 中的单词排序（升序）
            返回：排序后的字符串
          ```
          参考 makefile_str_sort
        + 取单词函数
          ```shell
            $(word <n>,<text>)
            功能：取字符串 <text> 中的第 <n> 个单词(n 从 1 开始)
            返回：<text> 中的第 <n> 个单词，如果 <n> 比 <text> 中单词个数要大，则返回空字符串
          ```
          参考 makefile_str_word
        + 取单词串函数
          ```shell
            $(wordlist <s>,<e>,<text>)
            功能：从字符串 <text> 中取从 <s> 开始到 <e> 的单词串，<s> 和 <e> 是一个数字
            返回：从 <s> 到 <e> 的字符串
          ```
          参考 makefile_wordlist
        + 单词个数统计函数
          ```shell
            $(words <text>)
            功能：统计字符串 <text> 中单词的个数
            返回：单词个数
          ```
          参考 makefile_str_words
        + 首单词函数
          ```shell
            $(firstword <text>)
            功能：取字符串 <text> 中的第一个单词
            返回：字符串 <text> 中的第一个单词
          ```
          参考 makefile_str_firstword
    + 文件名函数
        + 取目录函数
          ```shell
            $(dir <names...>)
            功能: 从文件名序列 <names> 中取出目录部分
            返回: 文件名序列 <names> 中的目录部分
          ```
          参考 makefile_file_dir
        + 取文件函数
          ```shell
            $(notdir <names...>)
            功能: 从文件名序列 <names> 中取出非目录部分
            返回: 文件名序列 <names> 中的非目录部分
          ```
          参考 makefile_file_notdir
        + 取后缀函数
          ```shell
            $(suffix <names...>)
            功能: 从文件名序列 <names> 中取出各个文件名的后缀
            返回: 文件名序列 <names> 中各个文件名的后缀, 没有后缀则返回空字符串
          ```
          参考 makefile_file_suffix
        + 取前缀函数
          ```shell
            $(basename <name...>)
            功能: 从文件名序列 <names> 中取出各个文件名的前缀
            返回: 文件名序列 <names> 中各个文件名的前缀, 没有前缀则返回空字符串
          ```
          参考 makefile_file_basename
        + 加后缀函数
          ```shell
            $(addsuffix <suffix>,<names...>)
            功能: 把后缀 <suffix> 加到 <names> 中的每个单词后面
            返回: 加过后缀的文件名序列
          ```
          参考 makefile_file_addsuffix
        + 加前缀函数
          ```shell
            $(addprefix <prefix>,<names...>)
            功能: 把前缀 <prefix> 加到 <names> 中的每个单词前面
            返回: 加过前缀的文件名序列
          ```
          参考 makefile_file_addprefix
        + 连接函数
          ```shell
            $(join <list1>,<list2>)
            功能: <list2> 中对应的单词加到 <list1> 后面
            返回: 连接后的字符串
          ```
          参考 makefile_file_join
    + foreach
      ```make
        $(foreach <var>,<list>,<text>)
      ```
      参考 makefile_foreach
    + if
      这里的 if 是个函数，和前面的条件判断不一样
      ```make
        $(if <condition>,<then-part>)
        $(if <condition>,<then-part>,<else-part>)
      ```
      参考 makefile_ifelse
    + call
      创建新的参数化函数
      ```make
        $(call <expression>,<parm1><pram2>,<parm3>...)
      ```
      参考 makefile_call
    + origin
      判断变量的来源
      ```make
        $(origin <variable>)
        类型              含义
        undefined           无定义
        default             缺省定义，如 CC
        environment         环境变量，并且 make 时没有使用 -e 参数
        file                定义在 Makefile 中
        command line        定义在命令行中
        override            被 override 重新定义过
        automatic           自动化变量
      ```
      参考 makefile_origin
    + shell
      ```make
        $(shell <shell command>)
      ```
      执行一个 shell 命令，并将 shell 命令的结果作为函数的返回
    + make 控制函数
        + 产生一个致命错误
          ```make
            $(error <text...>)
            功能：输出错误信息，停止 Makefile 的执行
            参考 makefile_make_error
          ```
        + 输出警告  
          ```make
            $(warning <text...>)
            功能：输出警告信息, Makefile 继续运行
            参考 makefile_make_warning
          ```
    
- Makefile 中一些 GNU 约定俗成的伪目标
  ```shell
    伪目标         含义
    all             所有目标的目标，其功能一般是编译所有的目标
    clean           删除所以被 make 创建的文件
    install         安装已编译好的程序，其实就是把目标可执行文件拷贝到指定的目录中去
    print           列出改变过的源文件
    tar             把源程序打包备份，也就是一个 tar 文件
    dist            创建一个压缩文件，一般是把 tar 文件压成 Z 文件，或是 gz 文件
    TAGS            更新所有的目标，以备完整地重编译使用
    check 或 test    一般用来测试 makefile 的流程
  ```
  常见伪目标
  ```shell
    make all        编译所有目标
    make install    安装已编译的程序
    make uninstall  卸载已安装的程序
    make clean      删除由 make 命令产生的文件，通常删除目标文件 .o
    make distclean  删除由 ./configure 产生的文件
    make check      测试刚编译的软件
    make installcheck   检查安装的库和程序
    make dist       重新打包成 packname-version.tar.gz
  ```
    
### 实际使用
- makefile 文件支持 include，即把一些基本依赖规则写在一个公共文件中，其他 makefile 文件包含此文件。
- 通常，公共 makefile 文件命名为 common.mk 。
- 一般在C/C++开发中，首先将源文件编译成目标文件(Windows下.obj文件，Unix下.o文件)——编译compile，再将
  目标文件合成执行文件——链接link。

### 编译 C 语言项目示例
```make
    edit : main.o kbd.o command.o display.o
        cc -o edit main.o kbd.o command.o display.o

    main.o : main.c defs.h
        cc -c main.c

    kbd.o : kbd.c defs.h command.h
        cc -c kbd.c

    command.o : command.c defs.h command.h
        cc -c command.c

    display.o : display.c defs.h
        cc -c display.c
        
    clean :
        rm edit main.o kbd.o command.o display.o
        
    .PHONY: edit clean
```
说明:
    + edit 为最后生成的可执行文件，make 时，如果没有指定目标，则执行第一个目标，即 edit。
    + make 会查找 edit 的依赖文件，即 main.o kbd.o command.o display.o, 如果没有或过期，则会调用
      其下面的过程依次生成这些依赖文件。


### 使用函数示例
```make
    CC = gcc 
    XX = g++ 
    CFLAGS = -Wall -O –g 
    TARGET = ./helloworld 

    %.o: %.c 
        $(CC) $(CFLAGS) -c $< -o $@ 

    %.o:%.cpp 
        $(XX) $(CFLAGS) -c $< -o $@ 
        
    SOURCES = $(wildcard *.c *.cpp) 
    OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES))) 

    $(TARGET) : $(OBJS) 
        $(XX) $(OBJS) -o $(TARGET) 
        chmod a+x $(TARGET) 
        
    clean: 
        rm -rf *.o helloworld
```
