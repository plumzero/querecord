
### 参考

[Lambda Expressions in C++](https://docs.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=vs-2017)


### 关键字

- capture clause                捕获从句
- lambda-introducer             引入符
- body of lambda expression     式体


### 概念和基本用法

- lambda 表达式提供了定义一个匿名函数对象(功能闭包)的简单方法，它能够捕获作用域中的一些变量。
- lambda 表达式是纯右值表达式，其类型是独有的无名非联合非聚合类类型，被称为闭包类型，它声明于含有该 lambda 表达式的最小块作用域、类作用域或命名空间作用域。
- lambda 的语法形式如下:
  ```c++
    [captures] (params) mutable -> return-type { body };
    [captures] (params)                        { body };
    [captures]                                 { body };
  ```
  其中:
    + capture   捕获列表；
    + params    参数表；
    + mutable   使按值捕获的变量可修改;
    + ret       返回值类型；
    + body      函数体；
  说明：
    + 示例如下:
      ```c++
        auto f = [](int a) -> int { return a + 1; };
      ```
    + 很多时候, lambda 表达式的返回值是很明显的，因此 c++ 11 中允许省略 lambda 表达式的返回值定义。
      ```c++
        auto f = [](int a) { return a + 1; }
      ```
    + lambda 表达式在没有参数列表时，参数列表是可以省略的。
      ```c++
        auto f1 = [] { return 1; }
      ```


### 捕获列表

- lambda 表达式可以通过捕获列表捕获一定范围内的变量：
    + `[]`        不捕获任何变量；
    + `[&]`       捕获外部作用域中所有变量，并作为引用在函数体中使用(按引用捕获);
    + `[=]`       捕获外部作用域中所有变量，并作为副本在函数体中使用(按值捕获);
    + `[=, &foo]` 按值捕获外部作用域中所有变量，并按引用捕获 foo 变量；
    + `[bar]`     按值捕获 bar 变量，同时不捕获其他变量；
    + `[this]`    捕获当前类中的 this 指针，让 lambda 表达式拥有和当前类成员函数同样的访问权限。如果已经使用了 & 或者 =, 就默认添加此选项。捕获 this 的目的是可以在 lambda 中使用当前类的成员函数和成员变量；
- 缺省时，lambda 表达式无法修改通过复制方式捕获的外部变量。如果希望修改这些变量的话，需要使用引用方式
  进行捕获。
  ```c++
    /** 示例一 */
    class A
    {
    public:
        int i_ = 0;
        
        void func(int x, int y)
        {
            auto x1 = [] { return _i; };                    // error, 没有捕获外部变量
            auto x2 = [=] { return i_ + x + y; }            // ok, 捕获所有外部变量
            auto x3 = [&] { return i_ + x + y; }            // ok, 捕获所有外部变量
            auto x4 = [this] { return i_; }                 // this 指针
            auto x5 = [this] { return i_ + x + y; }         // error, 没有捕获 x, y
            auto x6 = [this, x, y] { return i_ + x + y; }   // ok, 捕获 this 指针, x, y
            auto x7 = [this] { return i_++; }               // ok, 捕获 this 指针，并修改成员的值
        }
    };
    /** 示例二 */
    int a = 0, b = 1;
    auto f1 = [] { return a; };                 // error, 没有捕获外部变量
    auto f2 = [&] { return a++; };              // ok, 捕获所有变量，并修改 a
    auto f3 = [=] { return a; };                // ok, 捕获所有外部变量，并返回 a   
    auto f4 = [=] { return a++; };              // error, a 以复制方式捕获，无法修改
    auto f5 = [a] { return a + b; };            // error, 没有捕获 b
    auto f6 = [a, &b] { return a + (b++); };    // ok, 捕获 a 和 b 的引用，并对 b 作自加运算
    auto f7 = [=, &b] { return a + (b++); };    // ok, 捕获所有外部变量和 b 的引用，并对 b 作自加运算
    /** 示例三 */
    float f0 = 1.0;
    std::cout << [=] (float f) { return f0 + std::abs(f); } (-3.5) << std::endl;    // 4.5
  ```
- lambda 表达式的延迟调用
  ```c++
    int a = 0;
    auto f = [=] { return a; };
    a += 1;
    std::cout << f() << std::endl;      // 输出: 0
  ```
  在捕获的一瞬间, a 的值就已经被复制到 f 中了，之后 a 被修改，但此时 f 中存储的 a 仍然还是捕获时的值。在编程时对 lambda 表达式的延迟调用是一种不好的做法，不管是有意还是无意，应尽量避免。
- 通过显示指明 lambda 表达式为 `mutable` ，可以修改按值捕获的外部变量，且不影响实际的外部变量。
  ```c++
    int a = 0;
    auto f1 = [=] { return a++; };              // error, 按值捕获，无法修改
    auto f2 = [=] () mutable { return a++; }    // ok
  ```
  注意，被 mutable 修饰的 lambda 表达式就算没有参数也要写明参数列表；
- lambda 可以看作是一个仿函数，与 std::function 和 std::bind 一起使用
  ```c++
    std::function<int(int)> f1 = [](int a) { return a; };
    std::function<int(void)> f2 = std::bind([](int a) { return a; }, 123);
  ```


### 常见应用场景

- 应用于标准算法库对容器的操作，如 std::find_if, std::for_each 等。
  
  返回第一个大于 10 的元素:
  ```c++
    auto it = std::find_if(lst.begin(), lst.end(), [](decltype(*lst.begin()) & x) { x > 10; });
  ```
  查找大于 5 小于 10 的元素的个数:
  ```c++
    int count = std::count_if(coll.begin(), coll.end(), [](decltype(*coll.begin()) & x){ return x > 5 && x < 10; });
  ```
  容器内所有的元素依次加 10:
  ```c++
    std::for_each(vec.begin(), vec.end(), [](decltype(*vec.begin()) & x){ x += 10; });
  ```  

- 应用于关联容器的对象比较操作
  ```c++
    auto cmp = [](const Person& p1, const Person& p2) {
                return p1.lastname() < p2.lastname() ||
                    (p1.lastname() == p2.lastname() &&
                    p1.firstname() < p2.firstname());
                };
    ...
    std::set<Person, decltype(cmp)> coll(cmp);
  ```

- 创建线程
 
  创建一条线程:
  ```c++
    tid++;  // decltype(tid) == int
    std::thread th([](const int & tid){
        std::cout << tid << std::endl;
    }, std::cref(tid));
    th.detach();
  ```
  创建多条线程:
  ```c++
    std::vector<std::shared_ptr<std::thread>> threads;
    for (auto i = 0; i < 10; i++) {
        threads.emplace_back(std::make_shared<std::thread>([](const int & tid){
            // do sth
        }, std::cref(i)));
    }
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
  ```

- 作为工具独立使用:
  ```c++
    // 可以作为全局(就是放在 main 函数外面)可调用函数对象使用
    
    // 获取当前时间
    auto now_time = []() -> uint64_t {
        struct timeval tv;
        gettimeofday(&tv, nullptr);
        return tv.tv_sec * 1000 + tv.tv_usec / 1000;
    };
    std::cout << now_time() << std::endl;
    
    // 判断是否为素数
    auto isOdd = [](int x) -> bool {
        return x % 2;
    }
    std::cout << std::boolalpha << isOdd(3) << std::endl;
  ```
  
- 作为函数的入参使用，一般回调居多，简单的:
  ```c++
    template<typename ForwardIter, typename F>
    void change(ForwardIter first, ForwardIter last, F fun)
    {
        for (auto iter = first; iter != last; ++iter)
            *iter = fun(*iter);
    }
  ```
  形参 fun 接受任何适合的 lambda 表达式，也接受函数对象或普通的函数指针。编译器在这里并没有处理模板，而是在需要实例化一个模板时才会处理它。这里给出一个示例:
  ```c++
    int data[] { 1, 2, 3, 4 };
    change(std::begin(data), std::end(data), [](int value) { return value * value; })
  ```
  第二条语句会将 data 数组的元素全部替换为它们的平方值。

- 作为回调，复杂的:
  ```c++
    using FuncCallback = std::function<void(void)>;
    
    template<typename FuncCallback, typename Types... args>
    void handler(FuncCallback callback, Types&... args)
    {
        callback(args...);
    }
    
    auto cb_i = [](int i){ /** do sth */ };
    auto cb_d = [](double d){ /** do sth */ };
    auto cb_i_d = [](int i, double d){ /** do sth */ };
    
    handler(cb_i, 123);
    handler(cb_d, 5.89);
    handler(cb_i, 123, 5.89);
  ```
