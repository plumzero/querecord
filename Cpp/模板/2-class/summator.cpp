
#include <iostream>

/**说明: 1. 一个加法器。
 *       2. 对计算类型进行自动推导。
 *       3. 实现方式: 因为对类型更感兴趣，所以采用独立实现。
 */

/** 类型推导实现 */
/** 前向声明 */
template<typename... Types>
struct TypeOfSum;
/** 递归处理 */
template<typename T, typename... R>
struct TypeOfSum<T, R...>
{
    typedef decltype(typename TypeOfSum<T>::type() + typename TypeOfSum<R...>::type()) type;
};
/** 递归终止 */
template<typename T>
struct TypeOfSum<T>
{
    typedef T type;
};

/** 加法实现 */
template<typename T>
T sum(const T& in)
{
    return in;
}
template<typename T, typename... R>
typename TypeOfSum<T, R...>::type sum(const T& t, const R&... r)
{
    return t + sum(r...);
}

int main()
{
    std::cout << sum(5, -4, 10.52, 8.67) << std::endl;
}