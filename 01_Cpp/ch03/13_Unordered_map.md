

### 哈希表的构造

如果 C++ 已经为哈希表的键特例化 hash<K> 模板，那么可以像 map 一样构造哈希表。
```c++
    std::unordered_map<std::string, size_t> people { {"Jan", 44}, {"Jim", 33}, {"Joe", 99} };
    
    std::unordered_map<std::string, size_t> people {{{"Jan", 44}, {"Jim", 33}, {"Joe", 99}}, 10 };  // Bucket count: 10
    
    std::vector<std::pair<std::string, size_t>> folks { {"Jan", 44}, {"Jim", 33}, {"Joe", 99}, {"Dan", 22} };
    std::unordered_map<std::string, size_t> neighbors {std::begin(folks), std::end(folks), 500};    // Bucket count: 500
```

如果想要用自定义的对象作为键，那就必须为它定义一个哈希函数。如果还需要比较两个对象键，还需要定义一个恒等运算符。

[程序示例](13_Unordered_map/01_construct.cpp)


### 哈希函数

functional 头文件中定义了无序关联容器使用的特例化 `hash<K>` 模板。该模板定义了可以从 K 类型的对象生成哈希值的函数对象的类型。

`hash<K>` 实例的成员函数 operator()() 接受 K 类型的单个参数，然后返回 size_t 类型的哈希值。

对于基本类型、指针类型和 std::string，也定义了特例化的 `hash<K>` 模板。POD 类型(如 char, int, long, double 等)的哈希结果为原值。可以看出，如果哈希表的键为 POD 类型时，通过其原值就可以达到很好的哈希效果(无论是均匀度上还是计算量上)。

所以对于以 POD 为键的哈希表，应该使用缺省的哈希函数(不需要程序员定义)。

[程序示例](13_Unordered_map/02_hash_key.cpp)

但如果键并不是 POD 类型呢？程序员就需要自己定义哈希函数，也就是要**对 std::hash 偏特化**。

注意: 对模板类 std::hash 的特化使用要放在名字空间 std 中进行。

[程序示例](13_Unordered_map/03_hash_function.cpp)


### 哈希表长度与负载因子

在创建哈希表之前，最好预估一下要存储的元素数量，再按照负载因子确定哈希表长度。

负载因子是元素个数与哈希表长度之比，当容器达到最大负载因子时，会对容器中的元素重新哈希。

C++11 中最大负载因子默认为 1.0，可以通过成员函数 max_load_factor() 改变最大负载因子。通过 load_factor() 可以获取当前负载因子。

哈希表的长度通常取质数，这可以使哈希值更加均匀地分布在这个范围内。

在创建哈希表之后，一般会通过成员函数 rehash() 事先定义哈希表长度。

[程序示例](13_Unordered_map/04_rehash.cpp)


### 访问 Bucket

可以访问 unordered_map 的个别桶及其包含的元素。

桶的索引从 0 开始，可以通过将索引值传给容器的成员函数 begin() 重载版本来获取给定位置的格子中的第一个元素的迭代器。例如:
```c++
    auto iter = people.begin(1);
```

成员函数 bucket_count() 返回桶的个数。

成员函数 bucket() 返回键参数的桶索引位置。

成员函数 bucket_size() 返回索引参数指定的桶中的元素个数，其参数是 bucket() 返回的索引值。

[程序示例](13_Unordered_map/05_bucket.cpp)


### 插入与生成元素

参考 map 。


### 访问元素

调用 unordered_map 的 find() 会返回一个迭代器。这个迭代器指向和参数哈希值匹配的元素，如果没有匹配的元素，会返回这个容器的结束迭代器。

unordered_map 容器中的元素是无序，因此也不需要成员函数 upper_bound() 和 lower_bound()。成员函数 equal_range() 会返回一个以迭代器为成员的 pair，它指定了和参数匹配的一段元素。unordered_map 只可能有一个匹配元素。如果没有，两个迭代器都是容器的结束迭代器。

调用成员函数 count() 会返回容器中参数的出现次数，对于 unordered_map 只可能是 0 或 1 。


### 删除元素

参考 map 。


