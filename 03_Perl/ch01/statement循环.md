
### while控制结构

略


### until控制结构

在 while 控制结构中，只要表达式计算结果为真，就会继续执行循环，直到条件为假。

until 控制结构恰恰与此相反。

```pl
  until ($j > $i) {
    $j *= 2;
  }
```
该循环会一直执行，直到条件为真。


### 表达式修饰符

通过表达式修饰符简化代码:
```pl
  $i *= 2 until $i > $j;
  print " ", ($n += 2) while $n < 10;
```


### for控制结构

略


### foreach语句

略


### 循环控制

last next redo 操作符可以用在 5 种循环块中: for foreach while until 或是裸块({}) 。

如果有多层嵌套循环块，它们只会对内层起作用。

> last操作符

last 操作符能立即中止循环的执行，就像 C 语言中的 break 操作符一样。

同样地，last 操作符只会对当前运行中的最内层的循环块发挥作用。

> next操作符

next 会结束循环的当前迭代，继续执行循环的下一次迭代，类似于 C 语言中的 continue 。

同样地，next 操作符只会对当前运行中的最内层的循环块发挥作用。

> redo操作符

redo 操作符能将控制返回到当前循环块的顶端，而不经过任何条件测试，也不会进入下一次循环迭代。
```pl
  my @words = qw/ fred barney pebbles dino wilma betty /;
  my $errors = 0;
  
  foreach (@words) {
    ## redo 指令会跳到这里 ##
    print "Type the word '$_': ";
    chomp(my $try = <STDIN>);
    if ($try ne $_) {
      print "Sorry - That's not right.\n\n";
      $errors++;
      redo;   # 跳回循环的顶端
    }
  }
  print "You've completed the test, with $errors errors.\n";
```

next 和 redo 的最大区间在于，next 会正常继续下一次迭代，而 redo 则会重新执行这次的迭代。


> 带标签的块

略
