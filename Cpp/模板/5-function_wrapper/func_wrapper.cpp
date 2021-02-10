
#include <iostream>
#include <string>

template <class Function, class... Args>
inline auto FuncWrapper(Function && f, Args && ... args) -> decltype(f(std::forward<Args>(args)...))
{
    return f(std::forward<Args>(args)...);
}

void test0()
{
    std::cout << "test0" << std::endl;
}

int test1()
{
    std::cout << "test1" << std::endl;
    
    return 1;
}

int test2(int x)
{
    std::cout << "test2" << std::endl;
    
    return x;
}

std::string test3(std::string s1, std::string s2)
{
    std::cout << "test3" << std::endl;
    
    return s1 + s2;
}

int main()
{
    FuncWrapper(test0);             // 没有返回值，打印 1
    FuncWrapper(test1);             // 返回 1
    FuncWrapper(test2, 1);          // 返回 1
    FuncWrapper(test3, "aa", "bb"); // 返回 "aabb"
    
    return 0;
}