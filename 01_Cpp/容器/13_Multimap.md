
multimap 大部分成员函数的使用方式和 map 相同。因为重复键的原因， multimap 有一些函数的使用方式和 map 有一些区别。

这里介绍 multimap 的那些用法和 map 容器不同的成员函数。


### 插入

multimap 容器的成员函数 insert() 可以插入一个或多个元素，而且插入总是成功。

insert() 重载可以接受两个迭代器参数，用来指定插入元素的范围。

[插入程序示例](13_Multimap/01_insert.cpp)


### 在容器中生成元素

和 map 一个，multimap 的成员函数 emplace() 可以在容器的适当位置构造元素。

在插入具有相同键的元素时，可以使用 multimap 的成员函数 emplace_hint()，为这个函数提供一个迭代器形式的提示符来控制元素的生成位置。

[生成元素示例](13_Multimap/02_emplace.cpp)


### 查找元素

multimap 不支持下标运算，也不提供 at() 函数。

multimap 的 find() 成员函数可以返回一个键和参数匹配的元素的迭代器。

[find查找元素示例](13_Multimap/03_find.cpp)

如果需要访问给定键对应的所有元素，可以通过成员函数 equal_range() 实现。

成员函数 equal_range() 会返回一个封装了两个迭代器的 pair 对象，这两个迭代器所确定范围内的元素的键和参数值相等。

[equal_range查找元素示例](13_Multimap/04_equal_range.cpp)

成员函数 lower_bound() 会返回一个指向键值大于等于该参数的第一个元素，如果没有就指向结束迭代器。

成员函数 upper_bound() 会返回一个指向键值大于该参数的第一个元素，如果没有就指向结束迭代器。

同时使用 lower_bound() 和 upper_bound() 可以达到和 equal_range() 一样的效果。

[lower_bound和upper_bound查找元素示例](13_Multimap/05_lower_upper.cpp)


### 删除元素

multimap 的成员函数 erase() 有三个版本:

以待删除元素的迭代器作为参数，这个函数没有返回值。

以一个键作为参数，它会删除容器中所有含这个键的元素，返回容器中被移除元素的个数。

接受两个迭代器参数，指定要删除的一段元素，这个函数返回的迭代器指向最后一个被删除元素的后一个位置。

