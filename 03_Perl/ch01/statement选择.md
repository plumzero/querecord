
### if控制结构

略


### unless控制结构

在 if 控制结构中，只有当条件表达式为真时，才执行某块代码。

如果你想让代码块在条件为假时才执行，请把 if 改成 unless:
```pl
  unless ($fred =~ /\A[A-Z_]\w*\z/i) {
    print "The value of \$fred doesn't look like a Perl identifier name.\n";
  }
```
上述代码执行效果与下述代码一致:
```pl
  if (! ($fred =~ /\A[A-Z_]\w*\z/i)) {
    print "The value of \$fred doesn't look like a Perl identifier name.\n";
  }
```

unless 之后也可以加上一个 else 子句。可以想象得到，它可以理解为 if 控制语句中的 if 分支。


### 表达式修饰符

为了进一步简化代码书写，表达式后面可以接一下用于控制它行为的修饰符:
```pl
  print "$n is a negative number.\n" if $n < 0;
```
这实际上相当于一个 if 语句块。

同样地，也适用于 unless:
```pl
  print "$n is a negative number.\n" unless $n >= 0;
```


### elsif子句

略


### switch控制结构

switch case 执行是基于 Switch 模块， Switch 模块默认是没有安装的。可以通过 `cpan` 命令安装。输入 `cpan` 进入环境上下文，执行下列命令:
```s
  cpan[1]> install Switch           // 安装
  cpan[2]> exit                     // 退出
```

示例如下:
```pl
  use Switch;

  switch(argument)
  {
    case 1            { print "it's 1" }
    case "a"          { print "it' string a" }
    case [1..10,42]   { print "digital in the list" }
    case (\@array)    { print "digital in the array" }
    case /\w+/        { print "matched" }
    case (\%hash)     { print "hash" }
    case (\&sub)      { print "sub" }
    else              { print "not accord" }
  }
```
