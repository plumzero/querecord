
#include <iostream>

/**
 * 说明: 1. 求取类型长度之和。
 *       2. 对类型的推导应符合语义。
 *       3. 实现方式二: 独立实现，参考 std::integral_constant
 *       4. 当然，也可以使用枚举的方式实现，这里不作说明。
 */

/** 前向声明 */
template<typename... Types>
struct Sum;

/** 递归处理 */
template<typename T, typename... R>
struct Sum<T, R...>
{
    typedef decltype(sizeof(typename Sum<T>::type) + sizeof(typename Sum<T>::type)) type;
    static constexpr type value = Sum<T>::value + Sum<R...>::value;
    constexpr operator type() { return value; }
};
/** 
 *  下面的写法执行起来也能得到正确的结果，但它表示的是 Sum 计算的结果类型从 T 和 ...R 的 sizeof 中
 *  推导，而当前情形的语义应该是从对 T 以及 ...R 的 Sum 计算中推导。
 *  不符合语义，不推荐使用。
 */
// template<typename T, typename... R>
// struct Sum<T, R...>
// {
    // typedef decltype(sizeof(T) + sizeof...(R)) type;
    // static constexpr type value = Sum<T>::value + Sum<R...>::value;
    // constexpr operator type() { return value; }
// };

/** 递归终止 */
template<typename T>
struct Sum<T>
{
    typedef T type;
    static constexpr type value = sizeof(T);
};

int main()
{
    /** Sum 需要定义自己 operator T() 方法，才能像下面这样使用 */
    std::cout << Sum<int, double, short, int>() << std::endl;
    
    return 0;
}