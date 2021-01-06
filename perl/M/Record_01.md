
perl 模块安装是很简单的事情，当然这需要安装的目标环境上有两样东西: gcc 和 make 。

通常情况下，这两样东西环境都会提供，但有时也会出现没有 gcc 或 make 的情况。

怎么办呢？

一种办法是为环境装上 gcc 或 make ，之后就可以安装 .pm 模块了。

这里为了不污染环境，将其他地方编译好的 .pm 模块安置在目标环境的指定地方。

这里以安置 DBI 模块为例。


### 编译与打包

*编译环境操作*

在编译环境上编译生成 .pm 模块。

编译完成后对库打包:
```
    tar -zcvf perl.tar.gz perl/
```
perl/ 目录结构层次为:
```
    perl
    └── 5.22.1
        ├── ...
        ├── ...
        │  
```


实际上，这里打包的是安装后(即 make install)后的文件。因为编译出来的文件太多，且不太好筛选，所以才这样做。

不过，这并不算是一个坏办法。


### 安置

*目录环境操作*

将打包文件放到目标环境上，解压到 `/path/to/` 路径(不限定某个路径)下。


### 测试运行

编写一个 perl 文件，在其中添加 `BEGIN{push(@INC,"/path/to/perl/5.22.1")};` 。

```pl
    #!/usr/bin/env perl -w

    BEGIN{push(@INC,"/jingle/ATS/tools/perl/5.22.1")};

    use strict;

    BEGIN { $ENV{PERL_JSON_BACKEND}='JSON::PP'; }
    use JSON;

    my %rec_hash = (
                    'a' => 1,
                    'b' => 2,
                    'c' => 3,
                    'd' => 4,
                    'e' => 5
                   );

    my $json = encode_json(\%rec_hash);

    printf("%s\n", $json);
```

注意添加的目录层次要与打包一致。

完毕。

