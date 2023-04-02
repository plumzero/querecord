
std::packaged_task 模板类 - 包装一个可调用函数对象，并异步获取调用结果

### 声明

```c++
  template <class T> packaged_task;       // undefined
  template <class Ret, class... Args> class packaged_task<Ret(Args...)>;
```

### 说明

- std::packaged_task 内部也有一个 shared state, 用于存储 Args 调用 Ret 的结果，可以通过 std::future 对象实现对 shared state 的异步访问。  
- 通过调用 std::packaged_task::get_future 实现内部 shared state 与一个 std::future 对象关联。此函数调用后，返回的 std::future 对象与 std::packaged_task 对象共享 shared state 。  
  - std::packaged_task 对象对 shared state 的设置是异步的，它会在某一时刻设置 shared state 为 ready 。
  - std::future 对象是一个异步返回对象，它从 shared state 获取值，如有必要的话，还会等待 shared state ready 。

[测试程序](t/04_packaged_task.cpp)
