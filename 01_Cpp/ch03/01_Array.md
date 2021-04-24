
[array测试集](01_Array/README.md)

### 通过 `std::get<n>` 方法访问 `array<T>` 容器元素

在构造 `array<T, N>` 对象时，因为是在编译期指定数组长度，所以可以尝试在编译期指定获取元素的索引。 

C++ 提供了模板函数 `get<n>()`，它能够获取到容器的第 n 个元素。

`get<n>()` 模板提供了一种不需要在运行时检查，但能用安全的索引值访问元素的方式。

```c++
    std::array<std::string, 5> words { "one", "two", "three", "four", "five" };
    std::cout << std::get<3>(words) << std::endl;   // Output words[3]
    std::cout << std::get<6>(words) << std::endl;   // Compiler error message!
```

[程序示例](01_Array/04_get_n.cpp)
