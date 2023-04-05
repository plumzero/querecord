
存放一些代码段，供参考。

关于快速排序和二分查找，C语言标准库 'stdlib.h' 提供了相应的实现，分别是 `qsort` 和 `bsearch`。

比较浮点数是否相等:
```cpp
  bool equal(double d1, double d2)
  {
    if ((d1 - d2 > -0.0000001) && (d1 - d2 < 0.0000001))
      return true;
    else
      return false;
  }
```

整数(>0)数位之和:
```cpp
  int sum = 0;
  while (n) {
    sum += n % 10;
    n /= 10;
  }
```

统计字符串数组长度:
```cpp
  int len = -1;
  while (arr[++len]);
```

对于 int 类型，最大的正整数是`0x7FFFFFFF`，最小的负整数是 `0x80000000`。
正整数的防上溢出判断:
```cpp
  if (num >= 0 && num <= 0x7fffffff) { ... }
```
负整数的防下溢出判断:
```cpp
  if (num >= 0x80000000) { ... }
```

前后指针相向移动，在两指针相遇之前的判断:
```cpp
  while (pb < pe) {
    while (pb < pe && 右移条件充分)
      pb++;
    while (pb < pe && 左移条件充分)
      pe--;
    if (pb < pe) {
      // 对两个指向的元素进行的处理
    }
  }
```

遇到过下面这样的代码吗:
```cpp
  min = Min(a, b);
  if (min > certain) {
    // 执行处理
  }
```
不妨考虑写成下面这样:
```cpp
  if (a > certain && b > certain) {
    // 执行处理
  }
```

