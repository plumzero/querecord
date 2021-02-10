
## 关于容器

- [关联容器](关联容器.md)
- [函数对象](函数对象.md)
- [容器迭代器](容器迭代器.md)
- [容器算法](容器算法.md)
- [序列容器](序列容器.md)

## 设计一个映射类，可以使用 [] 语法糖
- 可以设计为类继承 std::map 类
  ```c++
    class MyMap : public std::map<std::string, std::string>
    {
        using StdMap = std::map<std::string, std::string>;
        
        MyMap() : StdMap() {}
        /** ... */
    };
  ```
  这样设计的话，可以使用 std::map 的语法糖 [] 操作符，但是对于 std::map 中
  的其他一些函数，比如 size() 需要自己重载，否则会出现未知行为，比较麻烦。
- 更推荐的做法，将 std::map 设计为类的成员，之后重载 [] 操作符
  ```c++
    class MyMap
    {
        std::map<std::string, std::string> mymap;
        /** ... */
    public:
        inline std::string operator[](std::string key) {
            return mymap[key];
        }
    };
  ```

## 顺便记录 C++ 容器的一些用法
- 只记录，不深究。

## 测试
- [resize使用时的注意事项](01-resize)
- [vector和list的push_back操作](02-push_back)
- [deque序列的数据结构](03-max_size)
- [list中remove和remove_if](04-list_remove)
- [list提供了sort函数](05-list_sort)
- [C++11的列表初始化](06-initialize_list)
- [std::string也是一种字符存储容器](07-string_vec)
- [0x12与'\x12'的区别](08-diff_12)
- [list::merge的使用](09-merge)
- [利用list实现一个环形队列](10-ring_list)
- [无序表与std::hash联合使用测试](11-unordered_map)


  
    