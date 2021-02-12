
## integral_constant 类
- 模板类 integral_constant 包装特定类型的静态常量，这样可以在编译时对类型进行检测。
- integral_constant 类是所有 traits 类的基类，C++11 定义如下:
  ```c++
    template <class T, T v>
    struct integral_constant {
        static constexpr T value = v;
        typedef T value_type;
        typedef integral_constant<T,v> type;
        constexpr operator T() { return v; }
    };
  ```
  constexpr 表示在编译时进行处理。

  其成员及功能如下:
    + `value_type`  表示值的类型
    + `value`       表示值
    + `type`        表示自身类型, 因此可以用 ::type::value 来获取 value

- C++11 定义的 traits 类大多继承自 integral_constant 类的特化类 true_type 类和 false_type 类，其定义如下:
  ```c++
    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;
  ```
- 除了 true_type 和 false_type, 使用者也可以根据需要通过 std::integral_constant 对类进行编译时处理。

## 利用 integral_constant 对自定义类型实现编译期处理
- 以自定义枚举类型为例，在 C++11 中通过从 `std::integral_constant` 派生一些类，而后再对这些类实例化后的对象进行处理时达到编译期判断目的。具体处理如下:

  **类型化。** 单纯的枚举类型是无法进行编译期判断的，通过 std::integral_constant 将枚举值类型化，这样就可以在编译期进行处理。
  ```c++
    // 单纯的枚举类型是无法进行编译期判断的
    typedef enum {
        VERSION_A,
        VERSION_B,
        VERSION_C,
    } TAG;
    
    // 通过 std::integral_constant 来将枚举值类型化，这样就可以在编译期进行类型判断了
    using A_type = std::integral_constant<TAG, VERSION_A>;
    using B_type = std::integral_constant<TAG, VERSION_B>;
    using C_type = std::integral_constant<TAG, VERSION_C>;
  ```
  
  **用户类型继承这种类型化的类。** 这里的用户类型即类似于下面的 struct VersionA, struct VersionB, struct VersionC。
  ```c++
    // 用户继承
    struct VersionA : A_type {
        int i;
    };

    struct VersionB : B_type  {
        double d;
    };

    struct VersionC : C_type {
        std::string s;
    };
  ```
  
  **通过类型特征(type traits)对不同的用户类型进行区分，实现编译期处理。**
  ```c++
    template <typename T>
    void parse_version(const T& t)
    {
        return parse_version(t, std::is_base_of<A_type, T>(),
                                std::is_base_of<B_type, T>(),
                                std::is_base_of<C_type, T>());
    }

    template <typename T>
    void parse_version(const T& t, const std::true_type&, const std::false_type&, const std::false_type&)
    {
        std::cout << "A type" << std::endl;
    }

    template <typename T>
    void parse_version(const T& t, const std::false_type&, const std::true_type&, const std::false_type&)
    {
        std::cout << "B type" << std::endl;
    }

    template <typename T>
    void parse_version(const T& t, const std::false_type&, const std::false_type&, const std::true_type&)
    {
        std::cout << "C type" << std::endl;
    }
  ```

  这之后，使用者就可以通过定义不同的用户类型来完成对函数的调用。
  ```c++
    VersionA va;
    parse_version(va);
    
    VersionB vb;
    parse_version(vb);
  ```
  [具体测试程序](01-integral_constant/integral_constant.cpp)

## 关于 integral_constant 的使用

布尔类型，枚举类型都是比较适合通过 integral_constant 来进行编译期处理的，因为它们的成员值是有限(不多)的。

像 int, double 等一些类型就比较坑，因为它们的成员范围太大了。

对于用户自定义类型，可以根据情况适时转换(比如继承自枚举类型)，来达到有限处理目的。

