
如果你自行定义了一个构造函数，那么编译器就不会再生成默认构造函数。如果你强制加上 `=default`，就可以重新获得并使用默认(default)构造函数。

如果不允许使用某种构造函数，可以加上 `=delete` 。这样在误用该种构造函数时，编译器就会报错:
```c++
    class Zoo
    {
    public:
        Zoo(){}
        Zoo(const Zoo&) = delete;
        Zoo& operator=(const Zoo&) = delete;
        Zoo(const Zoo&&) = default;
        Zoo& operator=(const Zoo&&) = default;
    };
```

`=default` 较少用在析构函数上，但不是不可以。

`=delete` 不能用到析构函数上。
