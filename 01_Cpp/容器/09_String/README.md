
[迭代器使用](01_iterator.cpp)

[利用string存储字符](02_initialize.cpp)

C++11 支持通过列表初始化构造 std::string, 可以像构造数组一样构造 std::string 。
数组构造形式如下:
```c++
    int arr[5]{ 0x12, 0x00, 0x24, 0x55, 0x03 };
```

但 std::string 不支持直接通过整数元素构造，因为 std::string 是存储字符的容器，
可以写成字符的形式构造，如下:
```c++
    std::string str{ '\x12', '\x00', 'x24', 'x55', '\x03' };
```

从上面也可以体会到 0x12 和 '\x12' 的区别，虽然值相同，但一个是整型数值，一个是字符。
std::string 是存储字符的容器，如果想要通过 std::string 保存数值，可以保存其同大小的字符。
