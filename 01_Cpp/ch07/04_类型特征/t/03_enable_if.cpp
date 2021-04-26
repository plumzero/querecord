
#include <string>
#include <iostream>
#include <type_traits>

/** 作用于返回值，用于选择类型重载 */
/** 能够隐式转换为 std::string 类型的重载方法 */
template <typename T>
typename std::enable_if<std::is_convertible<T, std::string>::value, std::string>::type
to_string(T r)
{
    return r;
}
/** 不能够隐式转换为 std::string 类型的重载方法 */
template <typename T>
typename std::enable_if<!std::is_convertible<T, std::string>::value, std::string>::type
to_string(T r) 
{
    return std::to_string(r);
}

/** 作用于入参，用于对入参进行限定 */
/** 第二个入参为计算类型时才能编译成功，此时第二个入参类型视为与第一个入参类型相同 */
template<typename T>
auto add(T t1, typename std::enable_if<std::is_arithmetic<T>::value, T>::type t2)
    -> decltype(t1 + t2)
{
    return t1 + t2;
}

/** 作用于模板参数，用于对模板参数类型进行限定 */
/** 模板参数类型均必须为计算类型 */
template <typename T1, typename T2, class = typename std::enable_if<std::is_arithmetic<T1>::value>::type,
                                    class = typename std::enable_if<std::is_arithmetic<T2>::value>::type>
auto sum(T1 t1, T2 t2) -> decltype(t1 + t2)
{
    return t1 + t2;
}

int main()
{
    /** [1] 作用于返回值 */
    std::cout << "作用于返回值:" << std::endl;
    {
        /** [1.1] 字符串类型 */
        char buf[] = { "Hello World" };
        std::cout << to_string(buf) << std::endl;
        
        const char* p = "hello world";
        std::cout << to_string(p) << std::endl;
        
        /** unsigned char 无法隐式转换为 std::string, 编译报错 */
        // unsigned char ubuf[] = { "HELLO WORLD" };
        // std::cout << to_string(ubuf) << std::endl;
        
        /** [1.2] 计算类型 */
        std::cout << to_string(3.14).c_str() << std::endl;
        std::cout << to_string(30).c_str() << std::endl;
        std::cout << to_string(38 + 2).c_str() << std::endl;
        std::cout << to_string(true).c_str() << std::endl;
    }
    /** [2] 作用于入参 */
    std::cout << "作用于入参:" << std::endl;
    {
        std::cout << add(1, 3.4) << std::endl;
        std::cout << add(3.4, 1) << std::endl;
        std::cout << add(4.6, 4.5) << std::endl;
        std::cout << add(5.5, true) << std::endl;
        std::cout << add(6.6, 'a') << std::endl;
        std::cout << add(-10.3, 4) << std::endl;
        std::cout << add(true, 5.6) << std::endl;
    }
    /** [3] 作用于模板参数 */
    std::cout << "作用于模板参数:" << std::endl;
    {
        std::cout << sum(3.14, 2.34) << std::endl;
        std::cout << sum(3, 2.34) << std::endl;
        std::cout << sum(3.14, 2) << std::endl;
        std::cout << sum(3, 2) << std::endl;
    }
    
    return 0;
}
