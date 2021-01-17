
*善始难善终*


### 用 s/// 进行替换

此操作符会把存在变量中匹配模式的那部分内容替换成另一个字符串，即将 `$&` 替换为指定的字符串。

```pl
    $_ = "He's out bowling with Barney tonight.";
    s/Barney/Fred/;
    print "$_\n";
```
如果匹配失败，则什么事都不会发生，变量也不受影响。

模式字符串与替换字符串还可以更加复杂:
```pl
    $_ = "He's out bowling with Barney tonight.";
    s/with (\w+)/against $1's team/;
    print "$_\n";
```

通过 `s///` 也可以将匹配到的字符串替换为空，达到删除效果。

> 用 /g 修饰符进行全局替换

缺省时 `s///` 只会进行一次替换，`/g` 修饰符可让 `s///` 进行所有符合正则要求的替换:
```pl
    $_ = "home, sweet home!";
    s/home/cave/g;
    print "$_\n";   # cave, sweet cave!
```

一个相当常见的全局替换就是缩减空白，即将任何连续的空白转换成单一空格:
```pl
    $_ = "Input  data\t may have    extra whitespace.";
    s/\s+/ /g;
```

删除开头和结尾的空白:
```pl
    s/^\s+//;
    s/\s+$//;
```
当然，也可以通过 `s/^\s+|s+$//g` 精简到一步，但这样会稍微慢一些。

> 使用不同的定界符

略。

> 可用替换修饰符

除了 `/g` 修饰符之外，也可以将 `/i /x /s` 修饰符用在替换操作中，联合使用时无需关心前后顺序。

> 绑定操作符

可以用绑定操作符为 `s///` 选择不同的替换目标:
```pl
    $file_name =~ s/^.*//;
```

> 无损替换

即同时保留原始字符串和替换后的字符串:
```pl
    (my $replaced = $original) =~ s/\d+ ribs?/10 ribs/;
```

> 大小写转换

把要替换的单词改成全部大写(或全部小写)，可以通过 `\U`(或`L`) 实现。

转成大写:
```pl
    $_ = "I saw Barney with Fred.";
    s/(fred|barney)/\U$1/gi;
```

转成小写:
```pl
    $_ = "I saw Barney with Fred.";
    s/(fred|barney)/\L$1/gi;
```

缺省情况下，`\U` 或 `\L` 会将其后的所有字符进行相应转换，如果需要在中间停止这种转换，可以通过 `\E` 关闭:
```pl
    $_ = "I saw Barney with Fred.";
    s/(\w+) with (\w+)/\U$2\E with $1/i;
```

使用小写形式的 `\l` 与 `\u` 时，它们只会影响紧跟其后的第一个字符。

[示例程序](../R/replace.pl)


### split 操作符

split 会根据给定的模式拆分字符串，**对于使用制表符、冒号、空白或任意符号分隔不同字段数据的字符串来说**，用这个操作符分解提取字段相当方便。

其用法示例如下:
```pl
    my @fileds = split(/separator/, $string);
```

将连续空白都视作单个空格并以此切分数据:
```pl
    my $some_input = "This is a \t    test.\n";
    my @args = split(/\s+/, $some_input);
```

值得注意的是，split 会保留开头处和中间的空字段，却会舍弃结尾处的空字段:
```pl
    my @fields = split(/:/, ":::abc:def::g:h:::");  # "" "" "" "abc" "def" "" "g" "h"
```

请避免在模式里使用捕获圆括号，如果需要在模式中使用分组匹配，请在 split 里使用非捕获圆括号(?:)的写法，以避免意外。

[示例程序](../R/split_join.pl)


### join 函数

join 函数不会使用模式。join 会将字符串片段接合成一个字符串，是 split 的反向操作。
```pl
    my $result = join($glue, @pieces);
```

如:
```pl
    my $x = join(":", (4, 6, 8, 10, 12));   # 4:6:8:10:12
```

与 split 结合使用:
```pl
    my $x = "4:6:8:10:12";
    my @values = split(/:/, $x);
    my $z = join("-", @values);
```

[示例程序](../R/split_join.pl)


### 在列表上下文中使用 m//

在列表上下文中使用 m// 时，如果模式匹配成功，那么返回的是所有捕获变量的列表；如果匹配失败，则返回空列表。

利用这个特性，就可以将匹配变量保存起来，供后续使用。

列表上下文中 - 保存为列表变量:
```pl
    $_ = "Hello there, neighbor!";
    my ($first, $second, $third) = /(\S+) (\S+), (\S+)/;
    print "$second is my $third\n"
```

列表上下文中 - 保存为数组:
```pl
    my $text = "Fred dropped a 5 ton granite block on Mr. Slate";
    my @words = ($text =~ /[a-z]+/ig);
    print "Result: @words\n";
```

列表上下文中 - 保存为哈希:
```pl
    my $data = "Barney Rubble Fred Flintstone Wilma Flintstone";
    my %last_name = ($data =~ /(\w+)\s+(\w+)/g);
```

[示例程序](../R/regexp_in_context.pl)


### 正则表达式的更强大功能

> 非贪婪量词

`+ *` 都是贪婪量词，会执行贪婪匹配。加上 `?` 后，即 `+? *?` 就是非贪婪匹配。

非贪婪匹配未必比贪婪匹配更有效率。这取决于目标串的长度及模式匹配规则。

非贪婪匹配主要用于一些格式化文本处理中，如 xml, html 等。


> 跨行的模式匹配

缺省时，Perl 的正则表达式都是用来匹配单行文本的。

在为模式加上 `/m` 修饰符之后，就可以用它们匹配字符串内的每一行了。
```pl
    $_ = "I'm much better\n than Barney is\nat bowling, \nWilma.\n";
    print "Found 'wilma' at start of line\n" if /^wilma\b/im;
```

将文件文件读入一个变量，并将文件名作为每一行的前缀进行替换:
```pl
    open FILE, $filename
        or die "Can't open '$filename': $!";
    my $lines = join '', <FILE>;
    $lines =~ s/^/$filename: /gm;
```

[示例程序](../R/regex_more.pl)
