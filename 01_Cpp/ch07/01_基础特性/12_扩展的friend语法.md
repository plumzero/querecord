
在 C++11 中，声明一个类为另外一个类的友元时，不再需要使用 class 关键字。这带来了一点应用上的变化，程序员可以为类模板声明友元了。
```c++
    class P;

    template <typename T> class People {
        friend T;
    };

    People<P> PP; // 类型 P 在这里是 People 类型的友元
    People<int> Pi; // 对于 int 类型模板参数，友元声明被忽略
```

[示例代码](t/12_friend.cpp)
