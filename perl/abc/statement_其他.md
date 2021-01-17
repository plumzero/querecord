
### 自增与自减

使用自增操作符(++)能将标量变量加 1:
```pl
    my $bedrock = 42;
    $bedrock++;
```

若有需要标量将会被自动创建。如用于检查列表中有哪些元素并计算每个元素出现的次数:
```pl
    my @people = qw/ fred barney fred wilma dino barney fred pebbles /;
    my %count;
    $count{$_}++ foreach @people;
```

类似地，自减:
```pl
    $bedrock--;
```

> 自增自减操作符的位置

即前置与后置的区别。

其语义与 C 语言相同。


### 三目操作符

略


### 逻辑操作符

`&& ||` 略

关于 `||`, 和 C 语言不同的地方在于，Perl 的短路操作符求得的值不只是简单的布尔值，而是最后运算的那部分表达式的值。
```pl
	my $last_name = $last_name{$someone} || '(No last name)';
```

在 Perl 中，可以利用逻辑或操作符的这个特性提供变量的默认值。
