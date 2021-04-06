
time_point 对象表示的是相对于某一时刻的瞬时时间，某一时刻由时钟(clock)定义，某一时刻到该瞬时时间的间隔由duration定义。

所以确定一个 time_point 需要两个要素，时钟和时间间隔(滴答)。

st::chrono::time_point 类模板定义了 time_point 类型:
```c++
    template <class Clock, class Duration = typename Clock::duration>
    class time_point;
```
这个模板有两个类型参数：提供某一时刻的时钟类型 Clock 以及 Clock 类型默认定义的 duration 类型。

[创建time_point](04_chrono/05_time_point_create.cpp)


### 时间点的持续时间

可以调用 time_point 对象的成员函数 time_since_epoch() 来得到表示从某一时刻到现在已流逝的时间的 duration 对象。

[参考](04_chrono/06_time_point_duration.cpp)

[计算两个时间点的间隔](04_chrono/06_time_point_timediff.cpp)


### 比较时间点

可以用运算符 `==`、`!=`、`<`、`<=`、`>=`和`>`中的任何一个来比较给定时钟的两个 time_point 对象。

比较的结果是通过比较为操作数调用 time_since_epoch() 后得到的结果产生的。

[参考](04_chrono/07_time_point_compare.cpp)


### 时钟的操作

除了第个时钟类型默认的构造函数之外，它们所有的成员函数都是静态的。所有时钟都包含一个含固定时间点、持续时间和 now() 函数的时刻。

静态成员函数 now() 会返回一个表示当前时间的 time_point 对象。

除了 3 个时钟类型都实现的 now() 函数之外，system_clock 还定义了两个静态成员函数，它们提供了 time_point 类型对象和定义在 ctime 头文件中的用来表示时间间隔 std::time_t 类型的对象之间的转换。

system_clock 的成员函数 `to_time_t()` 接受一个 time_point 参数，并以 time_t 类型返回它。成员函数 from_time_t() 则恰好相反。

[参考](04_chrono/08_time_point_ctime.cpp)

需要注意的是，因为 time_t 的单位是秒数，所以调用 to_time_t() 函数时可能会有一些精度损失。


