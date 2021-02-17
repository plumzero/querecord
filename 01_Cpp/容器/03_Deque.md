
[deque测试集](03_Deque/README.md)

### 关于 deque

deque 是一种双向开口的连续线性空间，可以在头尾两端分别做元素的插入和删除操作。

deque 是由一段一段的定量连续空间构成，一旦有必要在 deque 的前端或尾端增加新空间，便配置一段定量连续空间，串接在整个 deque 的头端或尾端。

deque 没有容量(capacity)概念，因为它是动态地以分段空间组合而成，随时可以增加一段新的空间并链接起来。

虽然 deque 也提供了 Random Access Iterator，但它的迭代器并不是普通指针，其复杂度大于 vector。因此，除非必要，我们应尽可能选择使用 vector 而非 deque。

对 deque 进行排序操作，为了提高效率，可将 deque 先完整复制一个 vector 中，将 vector 排序后(利用 STL sort算法)，再复制回 deque 。 

由于 deque 的元素没有被存放在数组中，所以也没有定义成员函数 data() 。


### 使用场景

无论何时，当应用包含先入先出的事务处理时，都应该使用 deque 容器。

处理数据库事务或模板一家超市的结账队列，像这两种应用都可以充分利用 deque 容器。

