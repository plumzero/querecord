
#include <iostream>
#include <functional>

void output(int x, int y)
{
    std::cout << x << " " << y << std::endl;
}

int main()
{
    std::bind(output, 1, 2)();                          // 输出: 1 2
    std::bind(output, std::placeholders::_1, 2)(1);     // 输出: 1 2
    std::bind(output, 2, std::placeholders::_1)(1);     // 输出: 1 2
    // std::bind(output, 2, std::placeholders::_2)(1);      // error: 调用时没有第二个参数
    std::bind(output, 2, std::placeholders::_2)(1, 2);  // 输出: 2 2
    std::bind(output, std::placeholders::_1, std::placeholders::_2)(1, 2);  // 输出: 1 2
    std::bind(output, std::placeholders::_2, std::placeholders::_1)(1, 2);  // 输出: 2 1
    
    return 0;
}