
### 说明

`shared_ptr<T>` 对象就像一个指向类型 T 的指针，和 `unique_ptr<T>` 不同的是，多个 `shared_ptr<T>` 可以指向同一个地址，因此 `shared_ptr<T>` 允许共享一个对象的所有权。

引用计数保存了指向给定地址的 `shared_ptr<T>` 的数量，每当一个新的 `shared_ptr<T>` 指针指向一个特定堆地址时，引用计数就会加 1 。当一个 `shared_ptr<T>` 被释放或者指向了新的地址时，引用计数就会减 1 。当没有 `shared_ptr<T>` 指向这个地址时，引用计数将会变成 0，在堆上为这个对象分配的内存就会自动释放。

[示例程序](t/02_sp_use_count.cpp)


### 构造与初始化

shared_ptr 支持所有构造，支持指针构造。

shared_ptr 不能通过直接将原始指针赋值来初始化，需要通过构造函数和辅助方法初始化。

通过构造函数与赋值构造函数初始化:
```c++
    std::shared_ptr<int> p(new int(1));
    std::shared_ptr<int> p2 = p;
```

[示例程序-构造](t/02_sp_construct.cpp)

除了通过构造函数创建 shared_ptr 外，C++11 还提供了更有效率的 std::make_shared 辅助函数来初始化 shared_ptr:
```c++
    std::shared_ptr<int> p3 = std::make_shared<int>(12);
```

对于一个未初始化的智能指针，可以通过 reset 方法初始化，当智能指针中有值的时候，调用 reset 会使引用计数减 1。
```c++
    std::shared_ptr<int> ptr;
    ptr.rest(new int(1));
```

[示例程序-reset](t/02_sp_reset.cpp)

注意: 只能通过拷贝构造函数或赋值运算符去复制一个 `shared_ptr<T>` 对象，通过一个由其他指针的 get() 函数返回的原生指针，来生成一个 `shared_ptr<T>` 指针，这可能会导致一些意想不到的问题。

如果将一个空指针赋给一个 `shared_ptr<T>` 对象，那么它的地址值将会变为空，同样也会使指针所指向对象的引用计数减 1 。例如:
```c++
    auto pname = std::make_shared<std::string>("Charles Dickens");
    pname = nullptr;        // Reset pname to nullptr
```


### 获取原始指针

当需要获取原始指针时，可以通过 get 方法来返回原始指针。
```c++
    std::shared_ptr<int> ptr(new int(1));
    int* p = ptr.get();
```

可以通过 unique 方法检查 `shared_ptr<T>` 对象是否有任何副本:
```c++
    auto pname = std::make_shared<std::string>("Charles Dickens");
    if (pname.unique()) {
        .. there is only one ...
    } else {
        .. there is more than one ...
    }
```
如果对象的实例数是 1, unique() 成员函数返回 true, 否则返回 false。

通过 use_count() 成员函数也可以知道当前有多少个实例。


### 指定删除器

删除器在运行时绑定。智能指针初始化时可以指定删除器:
```c++
    void DeleteIntPtr(int* p)
    {
        delete p;
    }
    std::shared_ptr<int> p(new int, DeleteIntPtr);
```
引用计数大于 1 时，仅会递减引用计数；use_count 等于 1 时，释放管理对象并递减引用计数；use_count 等于 0 时，自动调用删除器 DeleteIntPtr 来释放对象的内存。

删除器还可以是一个lambda 表达式:
```c++
    std::shared_ptr<int> p(new int, [](int *){ delete p; } );
```

[示例程序](t/02_sp_deleter.cpp)

当我们用 shared_ptr 管理动态数组时，需要自己指定删除器，因为 std::shared_ptr 的默认删除器不支持数组对象:
```c++
    std::shared_ptr<int> p(new int[10], [](int* p){ delete[] p; });
```
也可以将 std::default_delete 作为删除器。std::default_delete 的内部是通过调用 delete 来实现功能的:
```c++
    std::shared_ptr<int> p(new int[10], std::default_delete<int[]>());
```
另外，还可以通过封装一个 make_shared_array 方法来让 shared_ptr 支持数组:
```c++
    template<typename T>
    shared_ptr<T> make_shared_array(size_t size)
    {
        return shared_ptr<T>(new T[size], default_delete<T[]>());
    }
    
    // main
    std::shared_ptr<int> p = make_shared_array<int>(10);
    std::shared_ptr<char> p = make_shared_array<char>(10);
```


### shared_ptr 提供了与朴素指针相同的语法糖

`*`   解引用操作符

`->`  指针操作符

`=`   等号操作符(只支持移动构造或移动赋值构造)

`[]`  索引操作符

bool 操作符


### 使用 shared_ptr 需要注意的问题

- 不要用一个原始指针初始化多个 shared_ptr
  ```c++
    int* ptr = new int;
    std::shared_ptr<int> p1(ptr);
    std::shared_ptr<int> p2(ptr);       // logic error
  ```

- 不要在函数实参中创建 shared_ptr
  ```c++
    function (shared_ptr<int>(new int), g());   // 有缺陷
  ```
  不同的编译器，函数调用时入参顺序可能不同。如果入参顺序从右向左，且 g() 函数存在异常，则 shared_ptr 的使用就会出现问题。
  
  正确的写法应该是先创建智能指针，代码如下:
  ```c++
    std::shared_ptr<int> p(new int());
    f(p, g());
  ```

- 通过 shared_from_this() 返回指针。不要将 this 指针作为 shared_ptr 返回出来，因为 this 本质上是一个裸指针，直接通过 this 指针创建 shared_ptr 的话，可能会导致重复析构:
  ```c++
    struct A
    {
        std::shared_ptr<A> GetSelf()
        {
            return std::shared_ptr<S>(this);        // don't do this!
        }
    };
    
    // main
    std::shared_ptr<A> sp1(new A);
    std::shared_ptr<A> sp2 = sp1->GetSelf();
  ```
  上例中，由于同一个指针(this)构造了两个智能指针 sp1 和 sp2，而它们之间是没有任何关系的，在离开作用域之后 this 将会被构造的两个智能指针各自析构，导致重复析构的错误。
  
  正确返回 this 的 shared_ptr 的做法是: 让目标类通过派生 std::enable_shared_from_this<T> 类，然后使用基类的成员函数 shared_from_this 来返回 this 的 shared_ptr。
  std::enable_shared_from_this 类中有一个
  weak_ptr，这个 weak_ptr 用来观测 this 智能指针，调用 shared_from_this() 方法时，会调用内部这
  个 weak_ptr 的 lock() 方法，将所观测的 shared_ptr 返回。
  ```c++
    class A: public std::enable_shared_from_this<A>
    {
        std::shared_ptr<A> GetSelf()
        {
            return std::shared_from_this();
        }
    };
    
    std::shared_ptr<A> sp1(new A);
    std::shared_ptr<A> sp2 = sp1->GetSelf();      // ok
  ```
  在外面创建 A 对象的智能指针和通过该对象返回 this 的智能指针都是安全的，因为 shared_from_this()
  是内部的 weak_ptr 调用 lock() 方法之后返回的智能指针，在离开作用域之后，spy 的引用计数减为 0，
  A 对象会被析构，不会出现 A 对象被析构两次的问题。

- 要避免循环引用。智能指针最大的一个陷阱是循环引用，循环引用会导致内存泄露。
  
  具体见[这里](循环引用.md)


### 应用

通过智能指针管理第三方库分配的内存。
  
第三方库分配的内存一般需要通过第三方库提供的释放接口才能释放，由于第三方库返回的指针一般都是原始指针，在用完之后如果没有调用第三方库的释放接口，就很容易造成内存泄漏。
```c++
    void *p = GetHandle()->Create();
    // do something...
    GetHandle()->Release(p);
```
这段代码实际上是不安全的，在使用第三方库分配的内存过程中，可能忘记调用 Release 接口，还有可能中间不小心返回了，还有可能中间发生了异常，导致无法调用 Release 接口。

通过智能指针的性质，只要离开作用域内存就会自动释放，不用显式去调用释放接口了，也就不必担心上述接口调用问题:
```c++
    void* p = GetHandle()->Create();
    std::shared_ptr<void> sp(p, [this](void*p){GetHandle()->Release();});
```

将上述代码提炼出来，简化调用如下:
```c++
    std::shared_ptr<void> Guard(void* p)
    {
        return std::shared_ptr<void> sp(p, [this](void*p){GetHandle()->Release(p);});
    }
    void* p = GetHandle()->Create();
    auto sp = Guard(p);
    // do something...
```

上面的代码虽然简化了使用，但如果使用者像下面这样写的话，就不够安全:
```c++
    void *p = GetHandle()->Create();
    Guard(p);   // 危险
    // do something
```
上述代码中 Guard(p) 是一个右值，如果不将这个右值赋值给一个指针，则这句话结束之后，p 就被释放了，后面就会访问野指针的内容。

我们可以定义一个宏来解决这个问题:
```c++
    #define GUARD(p) std::shared_ptr<void> p##p(p, [](void*p){GetHandle()->Release(p);});
```
