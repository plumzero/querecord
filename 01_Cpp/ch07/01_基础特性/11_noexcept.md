
相比于断言适用于排除逻辑上不可能存在的状态，异常通常是用于逻辑上可能发生的错误。

### 作为修饰符

在 C++11 中，提供了 `noexcept` 修饰符，表示其修饰的函数`不会抛出异常`。如果修饰的函数抛出了异常，编译器可以选择直接调用 std::terminate() 函数来终止程序的运行，而不是像基于 throw() 的异常机制一样向外抛出，效率上更高一些。

从语法上讲，noexcept 修饰符有两种形式，一种就是简单地在函数声明后加上 noexcept 关键字。比如：
```c++
    void excpt_func() noexcept;
```
另外一种则可以接受一个常量表达式作为参数，如下所示：
```c++
    void excpt_func() noexcept (常量表达式);
```
常量表达式的结果会被转换成一个 bool 类型的值。该值为 true，表示函数不会抛出异常，反之，则有可能抛出异常。这里，不带常量表达式的 noexcept 相当于声明了 `noexcept(true)`, 即`不会抛出异常`。

在 C++11 中使用 noexcept 可以有效地阻止异常的传播与扩散。

[示例程序](t/11_block_throw.cpp)

### 作为操作符

noexcept 作为一个操作符时，通常可以用于模板。比如：
```c++
    template <class T>
        void func() noexcept(noexcept(T())) {}
```
在上面的代码中，每二个 noexcept 就是一个 noexcept 操作符。当其参数，也就是 `T()` 表达式是一个有可能抛出异常的表达式的时候，其返回值为 false, 反之为 true 。

这样一来，就可以使模板函数根据条件实现 noexcept 修饰的版本或无 noexcept 修饰的版本。

> 注意: `noexcept(true)` 表示修饰的函数不会抛出异常；`noexcept(false)` 表示修饰的函数会抛出异常，与普通函数无异。

虽然 noexcept 修饰的函数通过 std::terminate 的调用来结束程序的执行的方式可能会带来很多问题，比如无法保证对象的析构函数的正常调用，无法保证栈的自动释放等，但很多时候，“暴力”地终止整个程序确实是很简单有效的做法。事实上，noexcept 被广泛地、系统地应用在 C++11 的标准库中，用于提高标准库的性能，以及满足一些阻止异常扩散的需求。
```c++
    template <class T> class A {
        public:
            static constexpr T min() noexcept { return T(); }
            static constexpr T max() noexcept { return T(); }
            static constexpr T lowest() noexcept { return T(); }
    };

    void *operator new(std::size_t) noexcept(false);
    void *operator new[](std::size_t) noexcept(false);
```

当然，noexcept 更大的作用是保证应用程序的安全。比如`一个类析构函数不应该抛出异常`，那么对于常被析构函数调用的 delete 函数来说，C++11 默认将 delete 函数设置成 noexcept，就可以提高应用程序的安全性:
```c++
    void operator delete(void*) noexcept;
    void operator delete[](void*) noexcept;
```

