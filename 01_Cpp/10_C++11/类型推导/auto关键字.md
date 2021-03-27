
## auto 类型推导
- auto 是一种隐式类型推导；
- 不同于 Python 等动态类型语言的运行时变量类型推导，隐式类型定义的类型推导发生在编译器；
    ```c++
    auto x = 5;                 // ok x 是 int 类型
    auto pi = new auto(1);      // ok pi 被推导为 int*
    const auto *v = &x, u = 6;  // ok v 是 const int* 类型,u 是 const int 类型
    static auto y = 0.0;        // ok y 是 double 类型
    ```
- auto 并不能代表一个实际的类型声明，只是一个类型声明的占位符。所以使用 auto 声明的变量必须马上初始化，以让编译器推断出的它的实际类型，并在编译时将 auto 占位符替换为真正的类型；
- auto 限制
    + 不能用于函数参数；
    + 不能用于非静态成员变量；
    + 无法定义数组；
    + 无法推导出模板参数；
- auto 常用于推导模板容器中迭代器类型；