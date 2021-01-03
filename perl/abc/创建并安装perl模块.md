
[perl模块代码](../tests/Foo.pm)

#### 创建模块

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


#### 安装模块

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

#### 测试文件

[use测试](../tests/use.pl)

[require测试](../tests/require.pl)

为了防止污染系统目录，所以这里并没有安装及测试。

 

