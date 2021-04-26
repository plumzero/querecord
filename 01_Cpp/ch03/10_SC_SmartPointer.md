

当容器中保存的是原生指针或智能指针时，如果需要查找某个对象，那么总是需要为它们提供一个比较函数。如果不提供，就会对它们所保存的指针而不是指针所指向的对象进行比较。

常用智能指针有两种: `shared_ptr<T>` 和 `unique_ptr<T>`，这里也只说明这两种的使用方式。


### 选择智能指针

`shared_ptr<T>` 与 `unique_ptr<T>` 相比，前者执行得慢一些。就执行时间和内存使用而言，`unique_ptr<T>` 对象相对于原生指针开销最小。

如果需要在容器外部保存对象指针的副本，可以使用 `shared_ptr<T>`。如果不需要，应该使用 `unique_ptr<T>` 对象。

[程序示例](10_SC_SmartPointer/01_copy_ptr.cpp)


### 在优先级队列中存储智能指针

在这里，定义优先级队列时必须要提供比较函数，否则默认情况下就是对指针值而不是对象值的比较。

初始化是很关键的一步，不同的初始化方式对于不同类型智能指针适用性不同。比如，如果使用容器来初始化优先级队列，就不能选择 `unique_ptr<T>` 。 

[初始化示例](10_SC_SmartPointer/02_priority_queue_initialize.cpp)

无论是 `shared_ptr<T>` 或 `unique_ptr<T>`，均可以使用优先级队列成员函数 emplace() 或 push() 向队列中添加元素。

使用 push() 时，因为调用的是右值引用的重载版本，所以可以成功执行。

[添加元素示例](10_SC_SmartPointer/03_priority_queue_add.cpp)


### 指针的堆

当创建一个存储对象为指针的堆时，也需要提供一个用来比较对象的函数指针。

[程序示例](10_SC_SmartPointer/04_heap_ptr.cpp)


### 基类指针的容器

略


### 对指针序列应用算法

容器算法应用于存储对象为指针的容器时，也需要提供一个用来比较对象的函数指针。
```c++
    std::list<std::shared_ptr<std::string>> words {
        std::make_shared<std::string>("one"),
        std::make_shared<std::string>("two"),
        std::make_shared<std::string>("three"),
        std::make_shared<std::string>("four")
    };
    
    words.remove_if([](const std::shared_ptr<std::string>& p) { return (*pw)[0] == 't'; });
```