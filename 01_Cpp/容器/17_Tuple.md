
### 说明

tuple<> 模板是 pair 模板的泛化，但允许定义 tuple 模板的实例，可以封装不同类型任意数量的对象。因此 tuple 实例可以有任意数量的模板类型参数。


### 生成 tuple 对象

make_tuple() 函数可以接受不同类型的任意个数的参数，返回的 tuple 的类型由参数的类型决定。
```c++
    auto my_tuple = std::make_tuple(Name{"Peter", "Piper"}, 42, std::string{"914 626 7890"});
```
my_tuple 对象是 `tuple<Name, int, string>` 类型。如果提供给 make_tuple() 的第三个参数是一个字符串常量，my_tuple 的类型将是 `tuple<Name, int const char*>`, 这和之前的不同。

[创建tuple对象程序示例](17_Tuple/01_make_tuple.cpp)


### 比较运算符

可以用任何比较运算符(==, !=, <, <=, >, >=)来比较相同类型的 tuple 对象。tuple 对象中的元素是按照字典顺序比较的。

[程序示例](17_Tuple/02_compare.cpp)


### 获取 tuple 对象中的元素

函数模板 get<>() 可以返回 tuple 中的一个元素。第一个模板参数是 tuple 中元素的索引，从 0 开始。

也可以基于类型的 get<>() 从 tuple 获取元素，但要求 tuple 中只有一个这种类型的元素。

[利用get获取元素示例](17_Tuple/03_get.cpp)

tie<>() 函数提供了另一种访问 tuple 元素的方式。这个函数可以把 tuple 中的元素值通过赋值运算符"="转换为可以绑定到 tie<>() 的左值集合。

[利用tie获取元素示例](17_Tuple/04_tie.cpp)


### 使用 forward_as_tuple 更高效的传递 tuple 对象

当需要将一个对象传入函数时，为了避免拷贝开销，可以通过引用的方式传入。

如果需要将多个对象当作一个对象传给函数时，可以通过 tuple 将这些对象打包，为了避免拷贝开销，C++11 提供了 forward_as_tuple() 函数打包对象的引用。

此外，如果参数是一个临时对象， forward_as_tuple() 函数也会生成一个右值引用的 tuple 。
```c++
    const auto & c = std::forward_as_tuple(1, 2);
```
这里 c 的类型是 tuple<int&, int&> 。

也可以利用 forward_as_tuple() 构造 pair 对象。

[程序示例](17_Tuple/05_forward_as_tuple.cpp)

