
#include <iostream>
#include <type_traits>

class A
{
    A()=delete;
public:
    int operator()(int i)
    {
        return i;
    }
};

int main()
{
    std::result_of<A(int)>::type i = 4;     // 相当于 int i = 4
    
    std::cout << std::is_same<std::result_of<A(int)>::type, int>::value << std::endl;
    
    return 0;
}