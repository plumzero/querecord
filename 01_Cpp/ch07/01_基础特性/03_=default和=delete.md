
如果你自行定义了一个构造函数，那么编译器就不会再生成默认构造函数。如果你强制加上 `=default`，就可以重新获得并使用默认(default)构造函数。

如果不允许使用某种构造函数，可以加上 `=delete` 。这样在误用该种构造函数时，编译器就会报错:
```c++
  class Zoo
  {
  public:
    Zoo(){}
    Zoo(const Zoo&) = delete;
    Zoo& operator=(const Zoo&) = delete;
    Zoo(const Zoo&&) = default;
    Zoo& operator=(const Zoo&&) = default;
  };
```

`=default` 较少用在析构函数上，但不是不可以。

`=delete` 不能用到析构函数上。

在编程时，尤其是在使用模板时，应优先使用 delete，而非 private 来定义函数。

比如在一个类中定义一个成员模板函数 processPointer，同时又不想它对 void* 指针进行处理。如下:
```c++
  class Widget {
  public:
    ...
    template<typename T>
    void processPointer(T* ptr) { ... }
  private:
    template<>  // error!
    void processPointer<void>(void*);
  };
```
上面的代码对 void 类型的特化函数进行了 private 声明，然而实际并没有办法通过编译。

这里可以使用 delete 进行处理，如下:
```c++
  class Widget {
  public:
    ...
    template<typename T>
    void processPointer(T* ptr) { ... }
  };
  template<>  // error!
  void Widget::processPointer<void>(void*) = delete;  // public, but deleted
```
