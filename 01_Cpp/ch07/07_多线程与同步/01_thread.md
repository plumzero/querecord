
### 任务和线程

线程是任务在程序中的系统级表示。若要启动一个与其他任务并发执行的任务，C++11 中可构造一个 std::thread, 将任务作为它的参数。

这里，任务是以函数或函数对象的形式实现的：
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

另外，还可以通过 std::bind 或 lambda 表达式来创建线程：
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

线程不能复制，但可以移动。
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


### 线程的阻塞与非阻塞(分离)

std::thread 出了作用域之后将会析构，这时如果线程函数还没有执行完则会发生错误，因此，需要保证线程函数的生命周期在线程变量 std::thread 的生命周期之内。

可以通过 std::thread 的 join 成员函数在调用线程中阻塞 std::thread 线程，直到后者执行完毕。调用此函数后，thread 对象会成为 non-joinable 的，可以被安全地销毁。
```c++
    std::thread th([](){
        // ...
    });
    
    if (th.joinable()) {
        th.join();
    }
```
[示例程序-joinable](t/01_thread_joinable.cpp)

[示例程序-join](t/01_thread_join.cpp)


也可以通过 std::thread 的 detach 成员函数将 std::thread 线程与调用线程分离，使二者执行互不影响。资源在线程执行完毕之后各自释放。此方法被调用后，线程对象成为 non-joinable 的，并且可以被安全地销毁。
```c++
    std::thread th([](){
        // ...
    });
    
    th.detach();
```
[示例程序](t/01_thread_detach.cpp)


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
