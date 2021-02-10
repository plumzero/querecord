
#include <iostream>

/**
 * 说明: 可变参数函数示例，递归展开。
 */

/** 递归终止函数 */
void print(){}

/** 递归处理 */
template <typename T, typename... Types>
void print(T t, Types... r)
{
    std::cout << "parameter " << t << std::endl;
    print(r...);
}

int main()
{    
    print(1, "Hello World", 3.14, true);
    
    return 0;
}