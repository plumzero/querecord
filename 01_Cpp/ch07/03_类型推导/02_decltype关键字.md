
### decltype 关键字

`decltype` 用于推导出一个变量表达式的类型。使用 decltype 的推导过程也是在编译期完成的。

示例:
```c++
    int x = 0;
    decltype(x) y = 1;          // y -> int
    decltype(x + y) z = 0;      // z -> int
    
    const int &i = x;
    decltype(i) j = y;          // j -> const int &
    
    const decltype(z) *p = &z;  // *p -> const int, p -> const int *
    decltype(z) *pi = &z;       // *pi -> int     , p -> int *
    decltype(pi) *pp = &pi;     // *pp -> int *   , pp -> int **
```

### decltype(exp) 的推导规则

- exp 是标识符、类访问表达式, decltype(exp) 和 exp 的类型一致:
  ```c++
    class Foo
    {
    public:
        static const int Number = 0;
        int x;
    };
    int n = 0;
    volatile const int & x = n;
    
    decltype(n) a = n;                  // a -> int
    decltype(x) b = n;                  // b -> const volatile int &
    
    decltype(Foo::Number) c = 0;        // c -> const int
    Foo foo;
    decltype(foo.x) d = 0;              // d -> int, 类访问表达式
  ```

- exp 是函数调用, decltype(exp) 和返回值的类型一致:
  ```c++
    int& func_int_r(void);              // 左值(lvalue, 可简单理解为可寻址值)
    int&& func_int_rr(void);            // x 值(xvalue, 右值引用本身是一个 xvalue)
    int func_int(void);                 // 纯右值(prvalue)
    
    const int& func_cint_r(void);       // 左值
    const int&& func_cint_rr(void);     // x 值
    const int func_cint(void);          // 纯右值
    
    const Foo func_cfoo(void);          // 纯右值
    
    int x = 0;
    decltype(func_int_r())    a1 = x;   // a1 -> int &
    decltype(func_int_rr())   b1 = 0;   // b1 -> int &&
    decltype(func_int())      c1 = 0;   // c1 -> int
    
    decltype(func_cint_r())   a2 = x;   // a2 -> const int &
    decltype(func_cint_rr())  b2 = 0;   // b2 -> const int &&
    decltype(func_cint())     c2 = 0;   // c2 -> int
    
    decltype(func_cfoo())     ff = Foo();   // ff -> const Foo
  ```
  注意: c2 是 int 而不是 const int 。这是因为函数返回的 int 是一个纯右值(prvalue)。对于纯右值而言，只有类类型可以携带 cv 限定符，此外则一般忽略掉 cv 限定。
    
- 其他情况，若 exp 是一个左值，则 decltype(exp) 是 exp 类型的左值引用，否则和 exp 类型一致:
  ```c++
    struct Foo { int x; }
    const Foo foo = Foo();
    
    decltype(foo.x)     a = 0;          // a -> int
    decltype((foo.x))   b = a;          // b -> const int &
    
    int n = 0, m = 0;
    decltype(n + m)     c = 0;          // c -> int
    decltype(n += m)    d = c;          // d -> int &
  ```
  上面虽然说的很复杂，但实际应用时却不像上面那样复杂。

另外，标准库中有些类型都是通过 decltype 来定义的。
```c++
    typedef decltype(nullptr) nullptr_t;
    typedef decltype(sizeof(0)) size_t;
```


### decltype 的实际应用

- 应用于无法使用 `auto` 的情况下:
  ```c++
    int i;
    decltype(i) j;  // 事先声明一个 j
    // do other
  ```

- 应用在泛型编程中，用于改进泛型编程编码。

  对于下面的代码:
  ```c++
    template <class ContainerT>
    class Foo
    {
        typename ContainerT::iterator it_;  // 在使用时，若上下文要求传入一个 const 容
                                            // 器类型，则这里应使用 const_iterator
    public:
        void func(ContainerT& container)
        {
            it_ = container.begin();
        }
        // ...
    };
  ```
  可以使用 decltype 进行改写。
  ```c++
    template <class ContainerT>
    class Foo
    {
        decltype(ContainerT().begin()) it_;
    public:
        void func(ContainerT& container)
        {
            it_ = container.begin();
        }
        // ...
    };
  ```

- 函数对象类型推导(尤其是在一些lambda表达式中):
  ```c++
    class Task;
    
    auto handler = [](){};
    
    std::map<Task, decltype(handler)> mapth;
  ```


### 返回类型后置语法

- 为什么需要返回类型后置?
  ```c++
    template <typename R, typename T, typename U>
    R add(T t, U u)
    {
        return t + u;
    }
    int a = 1; float b = 2.0;
    auto c = add<decltype(a + b)>(a + b);
  ```
  我们并不关心 a + b 的类型是什么，所以传递一个模板参数 R 是多余的，因为这里完全可以通过 decltype(a + b) 来得到返回类型。
  
  所以可以改写成下面的形式:
  ```c++
    template <typename T, typename U>
    decltype(t + u) add(T t, U u)
    {
        return t + u;
    }
  ```
  
  但这样做的话，编译器在按顺序进行词法分析的时候，在到达 t 和 u 时并不清楚它们是哪种类型，因此通过 decltype 也就无法推导出 t + u 的类型是什么。
  
  为了解决函数返回值类型依赖于参数而导致难以确定返回值类型的问题。C++11 提供了返回类型后置语法，如下:
  ```c++
    template <typename T, typename U>
    auto add(T t, U u) -> decltype(t + u)
    {
        return t + u;
    }
  ```

  