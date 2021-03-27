
### 说明

priority_queue 的特征有两个，分别是队列和优先级。

既然是一个队列，所以只能访问第一个元素。

因为优先级，所以优先级最高的元素总是第一个被处理。

"优先级"的定义取决于使用者自己。


### 定义

priority_queue 模板有 3 个模板参数，第一个参数存储对象的类型，第二个参数是存储元素的底层容器，第三个参数是函数对象，它定义了一个用来决定元素顺序的断言，也就是"优先级"的定义。
```c++
    template<typename T, typename C = std::vector<T>, typename Compare = std::less<T>>
        class priority_queue;
```
后面两个模板参数有缺省参数，缺省时底层容器为 vector, 最大元素在前面。

通过第二个模板类型参数，也可以使用其他底层容器，只要它们支持 front()、push_back()、pop_back()、empty()、size() 这些操作。

使用其他优先级规则:
```c++
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
```


### 使用

1.[初始化](08_Priority_queue/01_initialize.cpp)

priority_queue 的操作可以参考 queue
