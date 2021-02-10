
#include <iostream>
#include <type_traits>

/**
 * 说明: 1. 求取类型长度之和。
 *       2. 对类型的推导应符合语义。
 *       3. 实现方式: 继承 std::integral_constant 递归
 */

/** 前向声明 */
template<typename... Types>
struct Sum;

/** 递归处理 */
template<typename T, typename... R>
struct Sum<T, R...>
    : std::integral_constant<decltype(sizeof(typename Sum<T>::value_type) + sizeof(typename Sum<R...>::value_type)),
                             Sum<T>::value + Sum<R...>::value>
{
};
/** 
 *  下面的写法执行起来也能得到正确的结果，但它表示的是 Sum 计算的结果类型从 T 和 ...R 的 sizeof 中
 *  推导，而当前情形的语义应该是从对 T 以及 ...R 的 Sum 计算中推导。
 *  不符合语义，不推荐使用。
 */
// template<typename T, typename... R>
// struct Sum<T, R...>
    // : std::integral_constant<decltype(sizeof(T) + sizeof...(R)), Sum<T>::value + Sum<R...>::value>
// {};

/** 递归终止 */
template<typename T>
struct Sum<T> : std::integral_constant<decltype(sizeof(T)), sizeof(T)>
{
};

int main()
{
    /** Sum 继承的 std::integral_constant 定义了 operator T() 方法，所以可以像下面这样使用 */
    std::cout << Sum<int, double, short, int>() << std::endl;
    
    return 0;
}