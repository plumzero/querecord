
## time_point

**time_point 表示一个时间点**，用来获取从它的 clock 的纪元(可以由程序员指定)开始所经过的 duration 。

time_point 有一个 `time_since_epoch()` 来获得 1970 年 1 月 1 日到 time_point 时间经过的 duration。下面是计算当前时间距离 1970 年 1 月 1 日有多少天的示例:
```c++
    typedef std::duration::<int, std::ratio<60*60*24>> days_type;   /** 以 86400 秒(即一天)为一个周期 */
    
    std::time_point<std::system_clock, days_type> today = 
                        std::time_point_cast<days_type>(std::system_clock::now());
    
    std::cout << today.time_since_epoch().count() << " days since epoch" << std::endl;
```

两个 time_point 相减的结果是 duration(时间段)。不同的时钟得到的时间单位各有不同，所以在实际使用时，最好把 duration 统一转换成一个公认的单位。可以通过 `duration_cast` 完成这一任务。
  
[system_clock的使用](02-time_point/system_clock.cpp)
