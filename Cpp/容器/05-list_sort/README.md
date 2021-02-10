
## 说明

排序是序列容器的一个基本操作，标准算法库提供了 std::sort 函数供序列容器进行排序:
```c++
    template <class RandomAccessIterator>
        void sort (RandomAccessIterator first, RandomAccessIterator last);

    template <class RandomAccessIterator, class Compare>
        void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);
```
这对 std::vector 很有用，因为 std::vector 自身并没提供 sort 函数。

一般不会对 std::deque 进行排序，纵使可以通过 std::sort 执行操作。

std::sort 只能对随机迭代器进行排序，而 std::list 的迭代器是双向的，所以 std::sort 并不能对 std::list 进行排序。

好在 std::list 自身提供了两个 sort 函数，分别与标准算法库提供的两个相对应:
```
    void sort();
    template<typename Compare> void sort(Compare comp);
```

## 测试内容

测试 std::list::sort 的使用。
