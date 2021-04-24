
[forward_list测试集](05_Forward_list/README.md)


### forward_list 使用注意

1.forward_list 与 list 的最主要区别是: 它不能反向遍历元素，只能从头到尾遍历。因此也无法使用反向迭代器。

2.forward_list 没有可以返回最后一个元素引用的成员函数 back()，只有成员函数 front()。

3.因为只能通过自增前面元素的迭代器到达序列的终点，所以 push_back()、pop_back()、emplace_back() 也无法使用。

4.forward_list 的迭代器是前向迭代器，它没有成员函数 size(), 不过可以通过 std::distance() 函数来得到元素的个数。

