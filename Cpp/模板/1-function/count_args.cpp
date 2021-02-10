
#include <iostream>

/**
 * 说明: 可变参数个数的统计
 */

/** 递归终止函数 */
void print(){}

/** 递归处理 */
template <typename T, typename... Types>
void print(T t, Types... args)
{
    std::cout << "sizeof...(args)=" << sizeof...(Types) << std::endl;
    print(args...);
}

int main()
{    
    print(1, "Hello World", 3.14, true);
    
    return 0;
}