
## duration 的定义

duration 表示一段时间间隔，用来记录时间长度，可以表示几秒、几分钟或者几个小时的时间间隔。
duration 的原型如下:
```c++
    template<
        class Rep, class Period = std::ratio<1, 1>
    > class duration;
```
第一个模板参数 Rep 是一个数值类型，表示时钟数的类型；第二个模板参数是一个默认模板参数 `std::ratio`, 表示时钟周期，它的原型如下:
```c++
    template<
        std::intmax_t Num,
        std::intmax_t Denom = 1
    > class ratio;
```
  **它表示每个时钟周期的秒数。**其中第一个模板参数 Num 代表分子，Demon 代表分母，**分母默认表示1**。因此 ratio 代表的是一个分子除以分母的分数值，比如 `ratio<2>` 代表一个时钟周期是两秒，`ratio<60>` 代表一分钟, `ratio<60*60>` 代表一个小时, `ratio<60*60*24>` 代表一天。而 `ratio<1, 1000>` 代表一毫秒, `ratio<1, 1000000>` 代表一微秒, `ratio<1, 1000000000>` 代表一纳秒。

为了方便使用，标准库定义了一些常用的时间间隔，如时、分、秒、毫秒、微秒和纳秒:
```c++
    typedef duration<Rep, ratio<3600, 1>>           hours;
    typedef duration<Rep, ratio<  60, 1>>           minutes;
    typedef duration<Rep, ratio<   1, 1>>           seconds;
    typedef duration<Rep, ratio<   1, 1000>>        milliseconds;
    typedef duration<Rep, ratio<   1, 1000000>>     microseconds;
    typedef duration<Rep, ratio<   1, 1000000000>>  nanoseconds;
```
hours 表示 3600 秒为一个周期，也就是一小时。minutes 表示 60 秒为一个周期，也就是分钟。milliseconds 表示 1 秒内有 1000 个周期，也就是 1 毫秒，等等。

通过定义的这些常用的时间间隔类型，可以方便地进行调用，比如线程的休眠:
```c++
    std::this_thread::sleep_for(std::chrono::seconds(3));           // 休眠 3 秒
    std::this_thread::sleep_for(std::chrono::milliseconds(100));    // 休眠 100 毫秒
```

## 获取时间间隔
chrono 提供了获取时间间隔的时钟周期数的方法 count(), 实际上就是获取每种时间间隔类型的模板参数中 ratio 的第二个参数类型的值与间隔值的乘积。其基本用法如下:
```c++
    std::chrono::hors h{10};            // h.count() = 10
    std::chrono::milliseconds ms{3};    // ms.count() = 3
```

时间间隔之间可以做运算，计算两端时间间隔的差值示例如下:
```c++
    std::chrono::minutes t1(10);
    std::chrono::seconds t2(60);
    std::chrono::seconds t3 = t1 - t2;
    std::cout << t3.count() << " seconds" << std::endl;
```
输出结果如下:
```c++
    540 seconds
```
利用这个可以计算两个时间点(相对于某一时间，如新纪元时间)之间的差值。

[count的使用](01-count/count.cpp)

