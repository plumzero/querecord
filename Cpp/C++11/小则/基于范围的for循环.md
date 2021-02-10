
## for 循环的新用法
```c++
    /** 只读方式遍历容器 */
    std::vector<int> arr = { 1, 2, 3 };
    for (auto n : arr)  // 使用基于范围的 for 循环
    {
        std::cout << n << std::endl;
    }
    /** 修改方式遍历容器 */
    int arrary[] = { 4, 5, 6};
    for (auto& n : arrary)
    {
        std::cout << n++ << std::endl;
    }
```

## 基于范围的 for 循环的使用细节
- 对 map 容器的 for 循环
  ```c++
    std::map<std::string ,int> mm = { {"1", 1}, {"2", 2}, {"3", 3} };
    for (auto& val : mm)
    {
        std::cout << val.first << " -> " << val.second << std::endl;
    }
  ```
  for 循环中 val 的类型是 std::pair 。因此，对于 map 这种关联性容器而言，需要使用 val.first 或 val.second 来提取键值。

  auto 自动推导出的类型是容器中的 value_type, 而不是迭代器。

- 同普通 for 循环一样，基于范围的 for 循环迭代时修改容器很可能会引起迭代器失效，导致一些未定义后果。

[iterator_range 实现示例](7-iterator_range/iterator_range.cpp)
