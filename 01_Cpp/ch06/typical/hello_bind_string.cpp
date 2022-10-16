
#include <string>
#include <functional>
#include <iostream>

struct StrCallable
{
    void operator()(std::string& x, const std::string& y, std::function<void(std::string&, const std::string&)> func)
    {
        func(x, y);
    }
};

void print_str(std::string& x, const std::string& y)
{
    std::cout << "print_str: " << x << "," << y << std::endl;
}

// 测试四
int main()
{
    {
        std::string str("hello");
        std::function<void(const std::string&)> binder = std::bind(StrCallable(), str, std::placeholders::_1, print_str);
        
        binder("world");
    }

    return 0;
}
