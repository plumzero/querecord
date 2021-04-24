
### 说明

`weak_ptr<T>` 对象只能从一个 `shared_ptr<T>` 对象创建，它们指向相同的地址。

创建一个 `weak_ptr<T>` 不会增加 `shared_ptr<T>` 对象的引用计数，所以它会阻止指向的对象销毁。

weak_ptr 可以用来返回 this 指针和解决循环引用的问题。


### 基本用法

- 通过 use_count() 方法来获得当前观测资源的引用计数
  ```c++
    std::shared_ptr<int> sp(new int(10));
    std::weak_ptr<int> wp(sp);
    
    std::cout << wp.use_count() << std::endl;       // 结果将输出 1
  ```

- 通过 expired() 方法来判断所观测的资源是否已经被释放
  ```c++
    std::shared_ptr<int> sp(new int(10));
    std::weak_ptr<int> wp(sp);
    if (wp.expired())
        std::cout << "weak_ptr 无效，所监视的智能指针已被释放" << std::endl;
    else
        std::cout << "weak_ptr 有效" << std::endl;
  ```
  std::weak_ptr 没有 `*` 运算符和 `->` 运算符，所以不能够对资源进行操作，它的唯一作用就是用于检查 std::shared_ptr 是否存在，其 expired() 方法能在资源未被释放时，会返回 false，否则返回 true。

- 通过 lock() 方法获取所监视的 shared_ptr
  ```c++
    std::weak_ptr<int> gw;
    void f()
    {
        if (gw.expired())   // 所监视的 shared_ptr 是否释放
        {
            std::cout << "gw is expired" << std::endl;
        }
        else
        {
            auto spt = gw.lock();
            std::cout << *spt << std::endl;
        }
    }
    
    // main
    {
        auto sp = std::make_shared<int>(42);
        gw = sp;
        f();
    }
    f();
  ```
  输出结果如下：
  ```c++
    42
    gw is expired
  ```
  