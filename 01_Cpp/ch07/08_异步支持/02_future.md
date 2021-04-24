

### std::future 模板类 - 异步执行结果的传输通道，获取异步函数的返回值

声明
```c++
    template <class T>  std::future;
    template <class R&> std::future<R&>;        // 特化 T 为引用类型
    template <>         std::future<void>;      // 特化 T 为 void 类型 
```

说明
* std::future 对象可以从给定的对象或函数 std::async 获取返回值。
* std::future 对象可以通过下列函数构造:        
    * std::async
    * std::promise::get_future  
    * std::packaged_task::get_future
* std::future 对象只在有效(valid)时可用。有效的(valid)的 std::future 对象会与 shared state 关联。缺省构造出的 std::future 对象是无效的，除非通过移动拷贝构造将其他有效对象"移动"过来。  
* 可以通过 std::future::get 获取存储在 shared state 上的值。


### 成员函数 std::future::get

声明
```c++
    T get();
    R& std::future<R&>::get();      // T 为引用类型
    void std::future<void>::get();  // T 为 void 类型
```
说明
* 在一个有效的 std::future 对象上调用其成员函数 std::future::get 时，会阻塞调用线程直到 shared state 被设置为 ready(设置值或产生异常)。通过这种方式可以实现线程的同步。  
* 一旦 shared state ready 之后，get 函数就会返回并释放 shared state ，此时 std::future 对象不再有效。


### 成员函数 std::future::wait_for

声明
```c++
    template <class Rep, class Period>
        std::future_status wait_for(const chrono::duration<Rep, Perion>& rel_time) const;
```
说明
* 在指定的时间 rel_time 内阻塞等待 shared stated，直到被设置为 ready 。超时返回。  
* 如果 shared state 关联的是一个延迟对象(如设置为延迟调用策略的 std::async 返回的 std::future 对象)，则该函数不会阻塞，立即返回 std::future_status::deferred 。

返回值
* std::future_status::ready    shared state ready
* std::future_status::timeout  超时
* std::future_status::deferred shared state 关联的是一个延迟对象


### std::shared_future 模板类 - std::future 对象不支持拷贝构造，这个支持拷贝构造

声明
```c++
    template <class T>  std::shared_future;
    template <class R&> std::shared_future<R&>;     // 特化 T 的引用类型
    template <>         std::shared_future<void>;   // 特化 void 的引用类型
```

说明
* std::shared_future 可以像 std::future 一样用来获取异步调用的结果。  
* std::future 不可拷贝，只能移动。而 std::shared_future 可以拷贝，比如当需要将 future 放到容器中时，就需要用到 std::shared_future 。  
* 除此之外，和 std::future 用法相同。

示例
```c++
    std::vector<std::shared_future<int>> vec;
    for (i = 0; i < 10; i++) {
        auto f = std::async(std::launch::async, [](int a, int b){ return a + b; }, 2, 3);
        vec.push_back(f);
    }
    for (const auto & ele : vec) {
        std::cout << ele.get() << std::endl;
    }
```
