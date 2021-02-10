
#include <iostream>
#include <functional>

class A
{
public:
    int x;
    int y;
    
    A() : x(0), y(0) {}
    ~A(){}
    
    void input(int i, int j)
    {
        x = i;
        y = j;
    }
};

int main()
{
    A a;
    
    std::cout << "a.x=" << a.x << ", a.y=" << a.y << std::endl;
    
    std::function<void(int, int)> fr = std::bind(&A::input, &a, std::placeholders::_1, std::placeholders::_2);
    
    fr(1, 2);
    
    std::cout << "a.x=" << a.x << ", a.y=" << a.y << std::endl;
    
    std::function<int&()> fr_x = std::bind(&A::x, &a);
    fr_x() = 123;
    
    std::cout << "a.x=" << a.x << ", a.y=" << a.y << std::endl;
    
    return 0;
}