
## clocks

clocks 包含如下 3 种时钟:
- system_clock: 代表真实世界的挂钟时间，具体时间值依赖于系统；
- steady_clock: 不能被"调整"的时钟，并不一定代表真实世界的挂钟时间；
- high_resolution_clock: 高精度时钟；

一般使用 high_resolution_clock 获取两个时钟，之后计算两个时钟之间的间隔较为多些。

[利用 high_resolution_clock 实现高精度测量时间](03-clocks/high_resolution_clock.cpp)

[利用 high_resolution_clock 实现一个计时器](03-clocks/timer.cpp)
