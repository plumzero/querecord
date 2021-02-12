
## 概述

std::deque 是一种双向开口的连续线性空间，可以在头尾两端分别做元素的插入和删除操作。
std::deque 是由一段一段的定量连续空间构成，一旦有必要在 std::deque 的前端或尾端增加新空间，便配置一段定量连续空间，串接在整个 std::deque 的头端或尾端。

std::deque 没有容量(capacity)概念，因为它是动态地以分段空间组合而成，随时可以增加一段新的空间并链接起来。
虽然 std::deque 也提供了 Random Access Iterator，但它的迭代器并不是普通指针，其复杂度大于 std::vector。因此，除非必要，我们应尽可能选择使用 std::vector 而非 std::deque。
对 std::deque 进行排序操作，为了提高效率，可将 std::deque 先完整复制一个 std::vector 身上，将 std::vector 排序后(利用 STL sort算法)，再复制回 std::deque 。 