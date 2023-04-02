
std::promise 模板类 - 设置一个值，将该值和 std::future 绑定起来，方便线程赋值

### 引入
    
主线程通过调用 std::async 函数开启一个子线程来执行异步操作，之后可以通过 std::future::get 访问 shared state 来获取执行结果。这个过程主线程只能通过 shared state 被动接收来自子线程的处理结果，而主线程无法向子线程供应任何数据；
    
std::promise 可以提供这样的功能。

### 声明

```c++
  template <class T>  std::promise;
  template <class R&> std::promise<R&>;       // 特化 T 为引用类型
  template <>         std::promise<void>;     // 特化 T 为 void 类型
```

### 说明

- 构造时，std::promise 对象与一个新的 shared state 关联，而程序员可以将一个 T 类型的值或 std::exception 类型异常存储到 shared state 上。
- 通过调用 std::promise::get_future 函数将处理好的 shared state 与一个 std::future 对象关联。调用该函数后，std::promise 对象和 std::future 对象共享这个 shared state 。
  - std::promise 对象的数据供应是异步的，它将会在某一时刻为 shared state 设置值(供应数据)。
  - std::future 对象是一个异步返回对象，它从 shared state 获取值(供应数据)，如有必要的话，还会等待 shared state ready 。

[测试程序](t/03_promise.cpp)
