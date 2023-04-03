
使用 `constexpr` 进行修饰，可以让程序在编译期就进行处理，以达到提高运行效率的目的。

### 常量表达式

对于常量表达式，如 `10 + 20`, `2 * 3`等，如果在编译期就可以直接得到最终结果，那么在运行期就不需要再次进行计算了。这样可以有效节约一部分运行效率。

[程序示例](t/05_expression.cpp)

### 函数

```c++
  constexpr int pow(int base, int exp) noexcept
  {
    // impl
  }

  constexpr auto numConds = 5;
  std::array<int, pow(3, numConds)> results;
```

[程序示例](t/05_function.cpp)

### 类

```c++
  class Point {
  public:
    constexpr Point(double x = 0, double y = 0) noexcept
      : _x(x), _y(y) {}
    constexpr double x() const noexcept { return _x; }
    constexpr double y() const noexcept { return _y; }
    void set_x(double x) noexcept { _x = x; }
    void set_y(double y) noexcept { _y = y; }
  private:
    double _x, _y;
  };
```

[程序示例](t/05_class.cpp)
