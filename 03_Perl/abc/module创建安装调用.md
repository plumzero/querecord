
[perl模块代码](../tests/Foo.pm)

### 创建模块

perl 5 中用包来创建模块。

在 Foo.pm 文件所在目录下执行如下命令:
```sh
    h2xs -AX -n Foo
```
执行后会有如下输出，并在当前目录下创建一个 Foo 目录。
```sh
    Writing Foo/lib/Foo.pm
    Writing Foo/Makefile.PL
    Writing Foo/README
    Writing Foo/t/Foo.t
    Writing Foo/Changes
    Writing Foo/MANIFEST
```
Foo 目录下新增文件说明如下:
```sh
    README： 这个文件包含一些安装信息，模块依赖性，版权信息等。
    Changes：这个文件作为你的项目的修改日志（changelog）文件。
    Makefile.PL：这是标准的 Perl Makefile 构造器。用于创建 Makefile.PL 文件来编译该模块。
    MANIFEST：本文件用于自动构建 tar.gz 类型的模块版本分发。这样你就可以把你的模块拿到 CPAN 发布或者分发给其他人。它包含了你在这个项目中所有文件的列表。
    Foo.pm ：这是主模块文件，包含你的 mod_perl 句柄代码（handler code）。
    Foo.t ：针对该模块的一些测试脚本。默认情况下它只是检查模块的载入，你可以添加一些新的测试单元。
    t/ ：测试文件
    lib/ ：实际源码存放的目录
```

之后，可以使用 tar 命令将以上目录打包，比如 Foo.tar.gz 。


### 安装模块

对刚才的压缩包 Foo.tar.gz 进行解压安装，执行步骤如下:
```pl
    tar -zxvf Foo.tar.gz
    cd Foo
    perl Makefile.PL
    make
    make test
    make install
```
执行 `perl Makefile.PL` 会生成编译所需要的 Makefile 文件。

perl 模块需要编译，从侧面可以说明，虽然是脚本，但运行速度应该不慢。

运行 `make install` 会将库文件安装到系统目录。


### 模块的调用

使用 require 或 use 进行模块的调用。

```pl
    #!/usr/bin/perl
    
    require Foo;
    
    Foo::bar("a");
    Foo::blat("b");
```

上述代码中，也可以将 require 替换为 use，如下:
```pl
    #!/usr/bin/perl
    
    use Foo;
    
    bar("a");
    blat("b");
```
可以看到，相比 require ，使用 use 不需要使用包名指定函数。

require 和 use 的区别:
- require用于载入module或perl程序(.pm后缀可以省略，但.pl必须有)
- use 语句是编译时引入的，require 是运行时引入的
- use 引入模块的同时，也引入了模块的子模块。而 require 则不能引入，要在重新声明
- use 是在当前默认的 @INC 里面去寻找,一旦模块不在 @INC 中的话,用 use 是不可以引入的，但是 require 可以指定路径
- use 引用模块时，如果模块名称中包含::双冒号，该双冒号将作为路径分隔符，相当于Unix下的/或者Windows下的\


### 测试文件

[use测试](../tests/use.pl)

[require测试](../tests/require.pl)

为了防止污染系统目录，所以这里并没有安装及测试。
