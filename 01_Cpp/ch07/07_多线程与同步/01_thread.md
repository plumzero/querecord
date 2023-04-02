
### 任务和线程

线程是任务在程序中的系统级表示。若要启动一个与其他任务并发执行的任务，C++11 中可构造一个 std::thread, 将任务作为它的参数。

任务可以以函数或函数对象的形式实现:
```c++
  void f();               // 函数
  
  struct F{               // 函数对象
    void operator()();  // F 调用运算符
  };
```

### 线程的创建

用 std::thread 创建线程只需要提供线程函数或者函数对象即可，并且可以同时指定线程函数的参数。

阻塞线程示例:
```c++
  void func()
  {
    // do some work
  }
  
  std::thread th(func);
```

创建可以接收任意个数的参数的线程:
```c++
  void func(int i, double d, const std::string& s)
  {
    // do some work
  }
  
  std::thread th(func, 1, 2, "test");
```

另外，在形式上也可以通过 std::bind 或 lambda 表达式来创建线程:
```c++
  void func(int a, double b)
  {
    // do some work
  }

  std::thread t1(std::bind(func, 1, 2));
  std::thread t2([](int a, double b){}, 1, 2);
```
[示例程序](t/01_thread_create.cpp)

### 线程的移动

线程不能被复制，但支持移动语义:
```c++    
  void func()
  {
    // do some work
  }
  
  std::thread t(func);
  std::thread t1(std::move(t));
```
上面的程序中，线程被移动之后，线程对象 t 将不再代表任何线程了。

利用这个特性，可以将线程对象保存到一个容器中，以保证线程对象的生命周期。
```c++
  {
    std::vector<std::thread> ths;
    
    std::thread th(func);
    ths.push_back(std::move(th));
  }
  
  {
    std::vector<std::shared_ptr<std::thread>> ths;
    ths.push_back(std::make_shared<std::thread>(func));
  }
```
  
当然也可以直接放入容器中:
```c++
  using thread_ptr = std::shared_ptr<std::thread>;
  std::vector<thread_ptr> ths;
  
  std::string str = "Hello World";
  ths.push_back(std::make_shared<std::thread>([](const std::string& s){
    // do some work
  }, std::cref(str)));
```

### 线程的 joinable

std::thread 出了作用域之后会进行析构，其析构函数如下:
```c++
  ~thread() {
    if (joinable()) {
      std::terminate();
    }
  }
```
如果在析构时，线程是 joinable 的，那么析构过程就会发生错误。比如下面的代码就会有析构风险:
```c++
  {
    std::thread th(f);
  }
```
为此，要保证在所有可能的情况下，std::thread 对象是 non-joinable 的。

std::thread 对象在以下情形下其状态是 non-joinable 的(也即可以安全析构):
- 默认构造函数产生
- 被 std::move(移出) 的 std::thread 对象
- 通过 join 方法挂起
- 通过 detach 方法分离

示例:
```c++
  std::thread th([](){
    // ...
  });
  
  if (th.joinable()) {
    th.join();
  }
```
- [示例程序-joinable](t/01_thread_joinable.cpp)
- [示例程序-join](t/01_thread_join.cpp)
- [示例程序-detach](t/01_thread_detach.cpp)


### 线程的释放

在 C++11 中将线程 std::thread 视作对象，它也有自己的析构函数(~thread)，线程对象在退出作用域时会自动调用析构。

当然，程序员也可以自己调用进行析构，这种情况在线程对象作为某个类的成员对象时更显得很有必要。
```c++
  class X
  {
    std::thread m_th;
    static bool is_running;
  public:
    X(){ m_th = std::thread(std::bind(&X::callback, this, std::ref(is_running))); }
    ~X(){}
    
    void clear_thread()
    {
      X::is_running = false;
      m_th.join();
      m_th.~thread();
    }
    
    void callback(const bool& running)
    {
      // ...
    }
  };
  
  X::is_running = true;
```
上述示例类在构造函数中创建了一个线程成员对象，但并不建议在析构函数(~X)中进行释放，因为你可能无法预料 X 的实例化对象具体是在哪种情形下释放的，这可能导致一些预料之外的效果。

为了避免这种情况，定义了 clear_thread 函数来释放线程成员对象。如下:
```c++
  {
    X x;
    x.clear_thread();   // 在调用 X 的析构函数之前调用 clear_thread 释放线程成员对象
  }
```

### 线程的其他使用

线程可以获取当前线程的ID，还可以获取 CPU 核心数量。
```c++
  std::thread th([](){
    // ...
  });
  
  std::cout << t.get_id() << std::endl;
  std::cout << std::thread::hardware_concurrency() << std::endl;
```

线程休眠
```c++
  void fuc()
  {
    std::this_thread::sleep_for(std::chrono::seconds(3));
  }
  
  std::thread th(fuc);
  th.join();
```
