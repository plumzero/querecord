
### 构造函数(重点)

unique_ptr 支持缺省构造、自定义构造以及移动构造和移动拷贝构造。
```c++
    constexpr unique_ptr() noexcept;
    explicit unique_ptr (pointer p) noexcept;
    template <typename U, typename E>
        unique_ptr (unique_ptr<U,E>&& x) noexcept;
```

unique_ptr 不支持拷贝构造和赋值拷贝构造(存有备份，与 unique_ptr 的惟一性语义冲突)。
```c++
    unique_ptr (const unique_ptr&) = delete;
```

unique_ptr 的缺省构造示例:
```c++
    std::unique_ptr<int> u1;
    std::unique_ptr<int> u2 (new int);
```

unique_ptr 不允许通过赋值将一个 unique_ptr 赋值给另外一个 unique_ptr:
```c++
    std::unique_ptr<int> u1, u2;
    // std::unique_ptr<int> u3 = u1;            /** 不支持拷贝构造 */
    std::unique_ptr<int> u4;
    // u4 = u2;                                 /** 也不支持赋值拷贝构造*/
```

unique_ptr 允许对象所有权的转移，这可以通过 std::move 来将一个 unique_ptr 指向的对象转移到另一个 unique_ptr 上:
```c++
    std::unique_ptr<int> u1, u2;
    std::unique_ptr<int> u3 = std::move(u1);    /** 移动构造 */
    std::unique_ptr<int> u4;
    u4 = std::move(u2);                         /** 移动拷贝构造 */
```
对象所有权转移后，原来的指针将失效。

[示例程序](01_unique_ptr/up_construct.cpp)


### 对指向对象所有权的释放

unique_ptr 通过成员函数 release 来实现对指向对象所有权的释放。
```c++
    pointer release() noexcept;
```
release 函数释放 unique_ptr 对一个对象的所有权，并返回一个指向该对象的朴素指针(pointer)，而 unique_ptr 将置空(null pointer)。

**此函数并不销毁所管理的对象**，只是 unique_ptr 自此不再对这个对象负责。也就是调用 release 后，该对象由程序员接管进行处理
```c++
    std::unique_ptr<int> u1 (new int);
    int * p;

    *u1 = 10;
    
    p = u1.release();   // 释放对象所有权后，u1 == nullptr

    if (直接释放) {
        delete p;
    } else if (由其他智能指针接管) {
        std::unique_ptr<int> u2;
    
        u2.reset(p);    // *u2 == 10
    }
```
[示例程序](01_unique_ptr/up_release.cpp)


### 对指向对象所有权的转移

```c++
    void reset(pointer p = pointer()) noexcept;
```
reset 函数将 unique_ptr 所管理的当前对象销毁，之后该 unique_ptr 将接管朴素指针 p 指向的对象。

如果 p 是一个空指针，则 unique_ptr 处于释放状态(相当于调用 release 后的状态)，此时可以用该 unique_ptr 去接管其他对象。
```c++
    std::unique_ptr<int> u1;

    u1.reset (new int);             // 接管
    *u1 = 5;                        // *u1 == 5

    u1.reset (new int);             // 销毁原来的对象，接管新对象。此时 u1 != nullptr, *u1 == 0

    *u1 = 10;                       // *u1 == 10

    u1.reset();                     // 销毁对象
```
[示例程序](01_unique_ptr/up_reset.cpp)


### 获取指向管理对象的指针

```c++
    pointer get() const noexcept;
```
原 unique_ptr 仍保有对该对象的管理权，也就是说获取的 pointer 指针并不能用来创建另外的 unique_ptr。


### 删除器(deleter)

一个 unique_ptr "拥有"一个对象(它所指向的)，某一个时刻，只能有一个 unique_ptr 指向一个给定的对象。当 unique_ptr 被销毁时，它所指向的对象也应被删除。这可以通过 unique_ptr 的删除器来实现。

unique_ptr 的删除器是编译时绑定的。

unique_ptr 有缺省的删除器(std::default_delete)，定义如下:
```c++
    template <class T> class default_delete;        // non-specialized  
    template <class T> class default_delete<T[]>    // array specialized

    std::default_delete::operator() 
    
    template <class T>
    void operator()(T* ptr) const;
```

unique_ptr 指定删除器的时候需要确定删除器的类型，所以不能像 shared_ptr 那样直接指定删除器:
```c++
    std::shared_ptr<int> ptr(new int(1), [](int *p){delete p;});
    std::unique_ptr<int, void(*)(int*)> ptr(new int(1), [](int *p){delete p;}); 
```
如果 lambda 表达式捕获了变量，上述 unique_ptr 的写法会编译报错。如果希望 unique_ptr 的删除器支持 lambda ，可以这样写:
```c++
    std::unique_ptr<int, std::function<void(int*)>> ptr(new int(1), [&](int *p){delete p;});
```

除此之外，使用者也可以自定义删除器。后者又分为两种形式: 左值删除器和右值删除器。

左值删除器(from pointer + lvalue deleter)
```c++
    unique_ptr<pointer p, typename conditional<is_reference<D>::value, D, const D&> del> noexcept;
```
根据缺省的删除器定义方法，可以定义自己的删除器。
[左值删除器示例](01_unique_ptr/up_deleter.cpp)

右值删除器(from pointer + rvalue deleter)
```c++
    unique_ptr<pointer p, typename remove_reference<D>::type&& del> noexcept;
```


### unique_ptr 指向数组
unique_ptr 和 shared_ptr 相比，unique_ptr 除了独占性这个特点之外，还可以指向一个数组，代码如下:
```c++
    std::unique_ptr<int []> ptr(new int[10]);
    ptr[9] = 9;             // 设置最后一个元素的值为 9
```
而下面的代码则是不合法的:
```c++
    std::shared_ptr<int[]> ptr(new int[10]);
```

### unique_ptr 提供了与朴素指针相同的语法糖

`*`   解引用操作符

`->`  指针操作符

`=`   等号操作符(只支持移动构造或移动赋值构造)

`[]`  索引操作符

bool 操作符


### make_unique 方法

C++11 中还没有为 unique_ptr 提供 make_unique 方法。这里通过 C++11 提供一种实现机制:
```c++
    namespace detail {
        template<bool B, typename T = void>
        using enable_if_t = typename std::enable_if<B,T>::type;

        /** 判断是否为动态数组 */
        template<typename T>
            struct is_unbounded_array_v : std::false_type {};
        template<typename T>
            struct is_unbounded_array_v<T[]> : std::true_type {};
         
        /** 判断是否为定长数组 */
        template<typename T>
            struct is_bounded_array_v : std::false_type{};
        template<typename T, std::size_t N>
            struct is_bounded_array_v<T[N]> : std::true_type{};
    }

    // 普通指针
    template<class T, class... Args>
        detail::enable_if_t<!std::is_array<T>::value, std::unique_ptr<T>>
    make_unique(Args&&... args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

    // 动态数组
    template<class T>
        detail::enable_if_t<detail::is_unbounded_array_v<T>::value, std::unique_ptr<T>>
    make_unique(std::size_t n)
    {
        typedef typename std::remove_extent<T>::type U;
        return std::unique_ptr<T>(new U[n]());
    }

    // 过滤掉定长数组情况
    template<class T, class... Args>
        detail::enable_if_t<detail::is_bounded_array_v<T>::value>
    make_unique(Args&&...) = delete;
```
在这里之所以定义 enable_if_t 是为了更好的体现其在第二个模板参数缺省时(void类型)的表现特征...欲辩已忘言，自己感受。

[示例程序](01_unique_ptr/make_unique.cpp)

### 应用

unique_ptr 指针可以作为对资源管理的一个句柄使用。

[示例程序](01_unique_ptr/up_resource.cpp)

