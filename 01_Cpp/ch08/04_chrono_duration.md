
### duration 的使用

`std::chrono::duration<T,P>` 模板类型表示 duration，其声明如下:
```c++
    template <class T, class P = ratio<1>>
    class duration;
```
模板参数 T 是值的类型，一般是基本的算术类型。可选参数 P 对应的值是时间刻度所表示的秒数，默认值为 1。可以通过 ratio 类型指定 P 的值来改变时间间隔。

为了方便叙述，这里将时间间隔称为滴答(tick) 。

`duration<T,P>` 的基本使用:
```c++
    // 1 秒 1 次滴答，共 60 次滴答(1 分钟)
    std::chrono::duration<int> minute { 60 };
    // 60 秒 1 次滴答，共 60 次滴答(1 小时)
    std::chrono::duration<double, std::ratio<60>> hour { 60 };
    // 1 秒 1000000 次滴答，共 1000 次滴答(1 毫秒)
    std::chrono::duration<long, std::micro> millisecond { 1000L };
    // 1 秒 5 次滴答，共 5.5 次滴答(1.1 秒)
    std::chrono::duration<double, std::ratio<1,5>> tiny { 5.5 };
```
std::micro 是定义于 ratio 头文件中对应于 ratio<1,1000> 的别名。除此之外，提供的常用别名还有:

|  别名  |         定义            |  说明  |
|:-------|:-----------------------|:-------|
| pico   | ratio<1,1000000000000> | 10e-12 |
| nano   | ratio<1,1000000000>    | 10e-9  |
| micro  | ratio<1,1000000>       | 10e-6  |
| milli  | ratio<1,1000>          | 10e-3  |
| centi  | ratio<1,100>           | 10e-2  |
| deci   | ratio<1,10>            | 10e-1  |
| deca   | ratio<10,1>            | 10e1   |
| hecto  | ratio<100,1>           | 10e2   |
| kilo   | ratio<1000,1>          | 10e3   |
| mega   | ratio<1000000,1>       | 10e6   |
| giga   | ratio<1000000000,1>    | 10e9   |

chrono 头文件为有整数类型值的常用持续时间类型定义了别名，如下:

|     别名     |                      定义                      |  说明   |
|:-------------|:-----------------------------------------------|:-------|
| hours        | duration<integer_type,ratio<3600, 1>>          |  小时  |
| minutes      | duration<integer_type,ratio<  60, 1>>          |  分钟  |
| seconds      | duration<integer_type,ratio<   1, 1>>          |  秒数  |
| milliseconds | duration<integer_type,ratio<   1, 1000>>       |  毫秒  |
| microseconds | duration<integer_type,ratio<   1, 1000000>>    |  微秒  |
| nanoseconds  | duration<integer_type,ratio<   1, 1000000000>> |  纳秒  |

interget_type 为整型类型，具体类型取决于系统。

用法示例:
```c++
    std::chrono::hours hs { 10 };
    std::chrono::minutes mi { 20 };
    std::chrono::milliseconds ms { 3 };
    std::chrono::microseconds us = { 4000 };
```


### duration 间隔数的获取

调用 duration 对象的成员函数 count() 可以返回间隔数，即滴答数。

```c++
    std::chrono::hours hs { 10 };
    hs.count();     // 10
    std::chrono::minutes mi { 20 };
    mi.count();     // 20
    std::chrono::milliseconds ms { 3 };
    ms.count();     // 3
    std::chrono::microseconds us = 2 * ms;
    us.count();     // 6000
```


### duration 之间的算术运算

可以将前缀或后缀自增和自减运算符应用到 duration 对象上，本质是对滴答数的自运算。

```c++
    std::chrono::duration<double, std::ratio<1,5>> tiny { 5.5 };
    std::chrono::microseconds very_tiny { 100 };
    ++tiny;
    very_tiny--;
    // tiny.count() = 6.5,  very_tiny.count() = 99
```

可以将任何二元算术运算符 `+`、`-`、`*`、`/`、`%` 应用到 duration 对象上，会得到一个 duration 对象作为结果。这些都是作为非成员运算符函数实现的。
```c++
    std::chrono::duration<double, std::ratio<1, 5>> tiny { 5.5 };
    std::chrono::duration<double, std::ratio<1, 5>> small { 7.5 };
    
    auto total = tiny + small;  // total 13
```

算术运算符也可以用不同类型的 `std::chrono::duration<T,P>` 模板实例，模板的两个参数都可以不同。对于 `duration<T1,P1>` 和 `duration<T2,P2>` 类型的参数，返回值为 `duration<T3,P3>`。T3 是 T1 和 T2 的共有类型，P3 是 P1 和 P2 的最大公因数。
```c++
    std::chrono::milliseconds ten_minutes { 600000 };
    std::chrono::minutes half_hour { 30 };

    auto total = ten_minutes + half_hour;   // total: 2400000 milliseconds = 40 minutes
```

所有可以应用到 duration 对象的算术运算符，都可以被用到左操作数是 duration 对象的复合赋值中，`+=` 和 `-=` 等这些运算的右操作数必须是 duration 对象。`*=` 和 `/=` 的右操作数必须和作为左操作数的时间刻度数(模板参数P)有相同类型的数值，或者可以隐式转换为数值。`%=`的右操作数可以是 duration 对象或数值。
```c++
    std::chrono::minutes short_time { 20 };
    std::chrono::minutes shorter_time { 10 };
    short_time += shorter_time;
    
    std::chrono::hours long_time { 3 };
    short_time += long_time;
    short_time.count();     // 210
```

[参考](04_chrono/01_duration_arithmetic.cpp)


### duration 之间的转换

通常，一个 duration 类型总是可以被隐式转换为另一个 duration 类型，如果模板参数 T 都是浮点型的话。
```c++
    std::chrono::duration<double, std::ratio<1, 5>> d1 { 50 };  // 10 seconds
    std::chrono::duration<double, std::ratio<1, 3>> d2 { 45 };  // 15 seconds
    
    d1 += d2;   // d1 = 125
```

当源类型的时钟周期是目的类型的时钟周期的整数倍时，只能对整数值进行隐式转换:
```c++
    std::chrono::duration<int, std::ratio<1, 5>> d1 { 50 };  // 10 seconds
    std::chrono::duration<int, std::ratio<1,10>> d2 { 50 };  //  5 seconds
    std::chrono::duration<int, std::ratio<1, 3>> d3 { 45 };  // 15 seconds
    std::chrono::duration<int, std::ratio<1, 6>> d4 { 60 };  // 10 seconds
    
    // d1 += d2;   // Won't compiled
    d2 += d1;      // OK
    // d3 += d4;   // Won't compiled
    d4 += d3;      // OK
```

可以显式地使用 duration_cast 模板进行强制转换:
```c++
    std::chrono::duration<int, std::ratio<1, 5>> d1 { 50 };  // 10 seconds
    std::chrono::duration<int, std::ratio<1,10>> d2 { 50 };  //  5 seconds
    std::chrono::duration<int, std::ratio<1, 3>> d3 { 45 };  // 15 seconds
    std::chrono::duration<int, std::ratio<1, 6>> d4 { 60 };  // 10 seconds
    
    d1 += std::chrono::duration_cast<std::chrono::duration<int, std::ratio<1, 5>>> (d2);
    d3 += std::chrono::duration_cast<std::chrono::duration<int, std::ratio<1, 3>>> (d4);
```

duration 类型支持赋值，因此可以将一个 duration 对象赋值给另一个 duration 对象。这可能会根据条件使用到隐式转换，否则需要对右操作数显式转换:
```c++
    std::chrono::duration<int, std::ratio<1, 5>> d1 { 50 };
    std::chrono::duration<int, std::ratio<1,10>> d2 { 53 };
    
    d2 = d1;    // d2 = 100
```

[参考](04_chrono/02_duration_convert.cpp)


### 比较 duration

有一整套完整的运算符可以用来比较两个 duration 对象。它们都是由非成员函数实现的，允许比较不同类型的 duration 对象。
```c++
    std::chrono::duration<int, std::ratio<1, 5>> d1 { 50 }; // 10 seconds
    std::chrono::duration<int, std::ratio<1,10>> d2 { 50 }; //  5 seconds
    std::chrono::duration<int, std::ratio<1, 3>> d3 { 45 }; // 15 seconds

    assert((d1 - d2) == (d3 - d1));
```

[参考](04_chrono/03_duration_compare.cpp)
