
## 说明

RingQueue 与 std::queue 对比:

底层数据结构为 std::list 时明显比 std::queue 慢许多。
底层数据结构为 std::deque 时也比 std::queue 慢一倍。不过在有些情况下比 std::queue 快一些。

std::deque 的底层数据结构太复杂了，RingQueue 如果使用的话，只能用定长。


## 测试内容

