
## final 关键字
- C++11 中增加了 final 关键字来限制某个类不能被继承，或者某个虚函数不能被重写。
- 如果修饰函数， final 只能修饰虚函数。
- final 要放到类或函数的后面。
- final 限制虚函数不能被重写示例:
  ```c++
    struct Base
    {
        // Base::foo is final, 限定该虚函数不能被重写
        virtual void foo() final {}
        // Error: non-virtual function cannot be final, 只能修饰虚函数
        // void bar() final;
    };

    struct Derived final : Base
    {
        // Error: foo cannot be overridden as it's final in A
        // void foo() {}
    };
  ```
  **通过限制带有虚函数的子类不被重写，可以让编译器更好地理解并优化程序。**
  
- final 限制类不能被继承:
  ```c++
    // struct Derived2 : Derived
    // {
    // };
  ```

## override 关键字
- 传统 C++ 中，当基类的虚函数被删除后，子类拥有旧的函数就不再重载该虚函数，并摇身一变成为了一个普通的类方法，这可能将造成灾难性的后果。
- 当重载虚函数时，引入 override 关键字将显式的告知编译器进行重载，编译器将检查基函数是否存在这样的虚函数，否则将无法通过编译。
- override 关键字确保在派生类中声明的重写函数在基类中存在，且与基类虚函数有相同签名。
- override 需要放到重写方法的后面。
- 使用示例
  ```c++
    struct Base
    {
        virtual void foo() {}
    };

    struct Derived : Base
    {
        virtual void foo() override;    // ok, 显示重写
        virtual void bar();             // ok, 新定义虚函数
        virtual void baz() override;    // error, 基类未定义 baz 虚函数
    };
  ```
