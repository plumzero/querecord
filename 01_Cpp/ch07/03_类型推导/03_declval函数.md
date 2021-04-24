

### std::declval 模板函数

语法
```c++
    template<typename T>
        typename add_rvalue_reference<T>::type declval() noexcept;
```

说明
+ 将任意类型 T 转换成引用类型，令在 decltype 表达式中不必经过构造函数就能使用成员函数。 
+ std::declval 只能用于不求值语境，且不要求有定义；求值包含此函数的表达式是错误的。
+ 关于返回值: 因为不能调用，从而决不返回值。返回类型是 T&& ，除非 T 是(可有 cv 限定的)void ,此情况下返回类型是 T 。
+ 该函数用于 unevaluated 操作符(如 sizeof 和 decltype)中。
+ 该函数用来在 unevaluated 操作符中引用一个类的成员，尤其是不清楚该类的构造函数或者无法创建类对象(如抽象类)时。

[使用示例](t/03_declval.cpp)
