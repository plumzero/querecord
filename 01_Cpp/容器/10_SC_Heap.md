
C++ 中关于堆的函数定义在头文件 algorithm 中。

### 创建堆

make_heap()对随机访问迭代器指定的一段元素重新排列，生成一个堆。默认使用 < 运算符，可以生成一个大顶堆。

make_heap()的重载版本可以用来指定一个比较函数，用于堆的排序。

[创建示例](10_SC_Heap/01_make_heap.cpp)


> priority_queue 与 make_heap 创建的堆比较

priority_queue 底层也是一个堆，与 make_heap() 创建的堆相比，priority_queue 可以提供堆没有的优势，它可以自动保持元素的顺序。

除了第一个元素，使用者无法直接访问 priority_queue 的其他元素，这可以有效避免外部打乱 priority_queue 内部的有序状态。

不过，虽然如此，使用 make_heap() 创建的堆可以提供一些 priority_queue 没有的优势:
- 可以访问堆中的任意元素，而不限于首部的第一个元素。这可能会有破坏元素顺序的可能，但是可以调用 make_heap() 来还原堆。
- 可以在任何提供随机访问迭代器的序列容器中创建堆。


### 向堆中添加元素

为了向堆中添加元素，首先可以用任何方法将元素附加到序列中。然后调用 push_heap() 来插入最后一个元素，为了保持堆的结构，这个元素会被重新排列到一个适当的位置。

具体操作是序列容器调用其成员函数 push_back() 在序列末尾添加元素，然后使用 push_heap() 恢复堆的排序。
```c++
    std::vector<double> v{ 2.5, 10, 3.5, 6.5, 8, 12, 1.5, 6 };
    
    std::make_heap(v.begin(),v.end());
    
    v.push_back(11);
    std::push_heap(v.begin(), v.end());
```
调用 push_heap() 时，它会认为最后一个元素是新元素，为了保持堆结构，会重新排列序列。这也说明，向序列容器添加元素时，必须从尾部插入。

在对通过指定比较函数创建的堆调用 push_heap 函数时，也必须传入该比较函数。

[添加示例](10_SC_Heap/02_push_heap.cpp)


### 从堆中弹出元素

即移除堆的首部元素。
```c++
    std::vector<double> v{ 2.5, 10, 3.5, 6.5, 8, 12, 1.5, 6 };
    
    std::make_heap(v.begin(),v.end());
    
    std::pop_heap(v.begin(), v.end());
    v.pop_back();
```

首先调用 pop_heap()，该函数会将第一个元素移到最后，并保证剩下的元素仍然是一个堆。之后调用序列容器成员函数 pop_back() 移除最后一个元素，实现堆的弹出操作。

在对通过指定比较函数创建的堆调用 pop_heap 函数时，也必须传入该比较函数。

[弹出示例](10_SC_Heap/03_pop_heap.cpp)


### 判断是否成堆

因为可能会打乱容器中的堆，所以 STL 提供了一个检查序列是否仍然是堆的方法 is_heap 。

[is_heap示例](10_SC_Heap/04_is_heap.cpp)

is_heap_until 可以更深入地检查元素中是否有部分元素为堆，它返回一个迭代器，指向第一个不在堆内的元素。如果整段元素都是堆，函数会返回一个结束迭代器。

[is_heap_until示例](10_SC_Heap/05_is_heap_until.cpp)


### 堆排序

sort_heap() 会将元素段作为堆来排序。如果元素段不是堆，程序会在运行时崩溃。

sort_heap() 会充分利用堆中数据的局部有序性对数据进行排序，这可以潜在地使排序变得更快。

[堆排序示例](10_SC_Heap/06_sort_heap.cpp)
