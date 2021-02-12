
## 背景

以 std::vector::resize 函数为例。

执行该操作时，会 value-initialized, 这会调用到容器元素的缺省构造函数。也即如果想要执行 resize, 则要求容器元素必须要有缺省构造函数。
可以看出，resize 会涉及到赋值，因而大量的 resize 操作会影响效率。

