
对于 new 来说，有 `new` 和 `::new` 之分，前者位于 std 。

`operator new()` 指对 new 的重载形式，它是一个函数，并不是运算符。对于 operator new 来说，分为全局重载和类重载，全局重载是 `void* ::operator new(size_t size)`，在类中重载形式为 `void *A::operator new(size_t size)`。

还要注意的是这里的 operator new() 完成的操作一般只是分配内存，事实上系统默认的全局 ::operator new(size_t size) 也只是调用 malloc 分配内存，并且返回一个 `void*` 指针，而构造函数的调用是在 new 运算符中完成的。

### new 和 operator new

```cpp
    A* a = new A;
```
完成对 A 对象的创建会分为两步，分别是分配内存和调用 A() 构造对象。分配内存这一操作是由 operator new(size_t) 来完成的，如果类 A 重载了 operator new, 那么将调用 A::operator new(size_t)，如果没有重载，就调用 ::operator new(size_t)，全局 new 操作符由 C++ 默认提供。

所以 new 操作符的执行过程是:
1. 调用 operator new 分配内存
2. 调用构造函数生成类对象
3. 返回相应指针

要实现不同的内存分配行为，可以重载 `operator new`。同样地，`operator new[]`、`operator delete`、`operator delete[]`也是可以重载的。

[operator new 重载示例]()

如果想要让对象只能建立在栈上，可以禁用 new 运算符，操作上将 operator new() 设为私有即可。代码如下:
```cpp
    class A
    {
    private:
        void* operator new(size_t) {}
        void operator delete(void* ptr) {}
    public:
        A() {}
        ~A() {}
    };
```