
std::async 模板函数 - 启动线程异步执行

std::async 是基于任务而非线程的。相比于直接创建创建(std::thread)，使用 std::async 不会抛出异常。

### 声明

```c++
  /** 版本一: 不指定策略，其实是按 async|deferred 策略执行的 */
  template<typename Fn, typename... Args>
  std::future<typename std::result_of<Fn(Args...)>::type>
    async(Fn&& fn, Args&&... args);
  /** 版本二: 指定策略 */
  template<typename Fn, typename... Args>
  std::future<typename std::result_of<Fn(Args...)>::type>
    async(std::launch policy, Fn&& fn, Args&&... args);
```

### 说明

- 异步调用 fn ，**不等执行完毕就立即返回。**
- fn 的返回值可以通过返回的 std::future 对象进行访问(调用 std::future::get)。
- 版本二允许事先选择一个指定的启动策略(std::launch::async 或 std::launch::deferred)。版本一的启动策略是自执行的(std::launch::async|std::launch::deferred)。
- 函数会将已经使用的线程句柄(针对版本一)或 fn(args) 未准备好(not ready)时的一份退化拷贝保存在 shared state 中。**一旦 fn 执行完毕，shared state 就会包含 fn 的返回值并设置已准备好(ready)**。

### 参数

- `policy` 位掩码值，指示启动策略
  - std::launch::async    启动一个新线程来调用 fn;
  - std::launch::deferred 延迟调用 fn 直到 std::future 返回的 shared state 可以(通过 wait 族或 get)访问。(说明: 调用返回时，std::future 返回的 shared state 被设置为 ready)。该策略提供了一种弹性机制，当新线程创建失败时(std::launch::aync 策略不生效时)，允许延迟(std::launch::deferred 生效)到主调线程中以同步方式去执行任务(执行时机为调用 wait 族或 get 方法时)。
  - std::launch::async|std::launch::deferred  fn 会自动选择执行策略。
- `fn` 可以是函数指针、成员函数指针或者可调用函数对象
  - fn 使用的是 args 的一份退化拷贝(decay copy)。
  - fn 的返回值会被作为 shared state 进行保存。这个 shared state 可以通过 std::async 返回的 std::future 对象获取。
  - 如果 fn 抛出异常，此异常也会设置到 shared state 中，由 std::future 获得。
- `args` 是传入 fn 的参数，是移动构造类型
  - 如果 fn 是一个成员函数指针，首参应该是该成员函数所属对象。

### 返回值

- fn 执行完毕后，std::future 的 shared state 会被设置为 ready 。通过 std::future::get 可以获取 shared state 。
- std::result_of::type 是 Fn 的返回值。


[测试程序](t/01_async.cpp)

[异步实现同步](t/01_async2sync.cpp)
