

### 包

perl 中的包可以理解为 C++ 语言中的名字空间。语法格式如下:
```pl
    package mypack;
```
此语句定义一个名为 mypack 的包，在此语句之后定义的所有变量和子程序的名字都存贮在该包关联的符号表中，直到遇到另一个 package 语句为止。

每个包中各自的符号表均有其自己的一组变量、子程序名。各包中符号表中的名字是互不关联的，因此可以在不同的包中使用相同的变量名，但代表的是不同的变量。

从一个包中访问另外一个包的变量，可通过 "package_name::variable_name" 方式指定。

缺省情况下，存贮变量和子程序的名字是与名为 main 的包关联的。

```pl
    # 缺省 main 包，使用默认的符号表
    $var = 1;
    print "package name: ", __PACKAGE__, " $var\n";     // package name: main 1
    
    package Foo;    # 从这里开始进入 Foo 包的势力范围
    $var = 10;
    print "package name: " __PACKAGE__, " $var\n";      // package name: Foo 10
    
    package main;   # 重新指定 main 包，使用默认的符号表
    $var = 100;
    print "package name: ", __PACKAGE__, " $var\n";     // package name: main 100
    print "package name: ", __PACKAGE__, " $Foo::var\n";// package name: main 10
```


### BEGIN 和 END 模块

perl 提供了 BEGIN 和 END 关键字，它们可以包含一组脚本，用于程序体运行前或者运行后的执行。

语法格式如下:
```pl
    BEGIN { ... }
    END { ... }
```

每个 BEGIN 模式在 perl 脚本载入和编译后，但在其他语句执行前执行。

每个 END 语句块在解释器退出前执行。

```pl
    package Foo;
    
    print "BEGIN 和 END 模块示例";
    
    BEGIN { print "这是 BEGIN 语句块\n"; }
    END { print "这是 END 语句块\n"; }
```


### 模块与包

perl 模块是一个可重复使用的包，模块的名字与包名相同，定义的文件后缀为 .pm 。

定义一个名字为 Foo.pm 的模块作为示例进行说明:
```pl
    #!/usr/bin/perl
    
    package Foo;
    
    sub bar {
        print "Hello $_[0]\n";
    }
    
    sub blat {
        print "World $_[0]\n";
    }
    1;
```
perl 中关于模块需要注意以下几点:
- 函数 require 和 use 将载入一个模块
- @INC 是 perl 内置的一个特殊数组，它包含指向库例程所在位置的目录路径
- require 和 use 函数调用 eval 函数来执行代码
- 末尾的 "1;" 表示执行返回 TRUE,是必须的，否则返回错误
