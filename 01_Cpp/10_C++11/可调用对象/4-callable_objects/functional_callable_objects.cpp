
#include <iostream>
#include <functional>

/**
 * std::function 绑定函数指针、可被转换为函数指针的类对象、函数对象
 */

void func(void)
{
    std::cout << __FUNCTION__ << std::endl;
}

class Foo
{
public:
    static int foo_func(int a)
    {
        std::cout << __FUNCTION__ << "(" << a << ") ->: ";
        return a;
    }
};

class Bar
{
public:
    int operator()(int a)
    {
        std::cout << __FUNCTION__ << "(" << a << ") ->: ";
        return a;
    }
};

int main()
{
    std::function<void(void)> fr1 = func;           // 绑定一个普通函数
    fr1();
    
    std::function<int(int)> fr2 = Foo::foo_func;    // 绑定一个类的静态成员函数
    std::cout << fr2(123) << std::endl;
    
    Bar bar;
    std::function<int(int)> fr3 = bar;              // 绑定一个仿函数
    std::cout << fr3(123) << std::endl;

    return 0;
}