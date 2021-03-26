
STL 定义的时钟类型提供了硬件时钟或操作系统时钟的接口。时钟有时钟周期，时间是通过时钟周期数来衡量的。

std::chrono 定义了 3 种时钟。

### 时钟类型

system_clock 类封装了当前真实时钟时间。尽管它一般都在增加，但在有些时候也会减少。比如，在冬季和夏季会按照季节调整，在不同的时区 system_clock 也会发生改变。

steady_clock 类封装了一个适合记录时间间隔的时钟。这个时钟总是在增加，不能减小。

high_resolution_clock 的实例是一个具有当前系统所能使用的最小时钟周期的时钟。在一些实现中，它可能是 system_clock 或 steady_clock 的别名，在这种情况下没有提供额外的 high_resolution_clock 。

system_clock 通常不是稳定的时钟，因为它无法保证时间总是增加，而且系统活动会影响时间刻度之间的时间。steady_clock 因为稳定特性常用于测量时间间隔。可以通过静态数据成员 `is_steady` 判断是否为稳定的时钟:
```c++
    std::cout << std::boolalpha << std::chrono::system_clock::is_steady << std::endl;
    std::cout << std::boolalpha << std::chrono::steady_clock::is_steady << std::endl;
    std::cout << std::boolalpha << std::chrono::high_resolution_clock::is_steady << std::endl;
```

[参考](04_chrono/04_clock_is_steady.cpp)
