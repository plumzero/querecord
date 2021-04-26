
1.[初始化](01_list_initialize.cpp)

2.[容量增加造成内存重分配测试](02_list_emplace.cpp)

3.[利用remove和remove_if移除指定值](03_list_remove.cpp)

4.[利用unique移除连续的重复元素](04_unique.cpp)

可以在对元素进行排序后，再使用 unique()，这样可以保证移除序列中全部的重复元素。

5.[利用sort排序元素](05_sort.cpp)

全局 sort() 函数模板定义在头文件 algorithm 中，要求使用随机访问迭代器。但 list 容器并不提供随机迭代器，只提供双向迭代器，因此不能对 list 中的元素使用全局 sort() 算法。但是，list 容器定义了自己的 sort() 成员函数。

6.[利用merge合并容器](06_merge.cpp)

用作合并的两个容器必须是升序的。

7.[利用splice剪切容器](07_splice.cpp)

成员函数 splice() 用于将参数 list 容器中的元素移动到当前容器中指定位置的前面。

可以移动单个元素、一段元素或源容器的全部元素。
