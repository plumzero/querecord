
#include <iostream>
#include <type_traits>

// 通用
template<typename T>
struct is_integral : std::false_type {};

// 这些情况下特化为 true
template<>
struct is_integral<bool> : std::true_type {};
template<>
struct is_integral<char> : std::true_type {};
template<>
struct is_integral<char16_t> : std::true_type {};
template<>
struct is_integral<char32_t> : std::true_type {};
template<>
struct is_integral<wchar_t> : std::true_type {};
template<>
struct is_integral<short> : std::true_type {};
template<>
struct is_integral<int> : std::true_type {};
template<>
struct is_integral<long> : std::true_type {};
template<>
struct is_integral<long long> : std::true_type {};

int main()
{
    std::cout << std::boolalpha;
    
    std::cout << "char is integral? " << is_integral<char>::value << std::endl;
    std::cout << "char16_t is integral? " << is_integral<char16_t>::value << std::endl;
    std::cout << "wchar_t is integral? " << is_integral<wchar_t>::value << std::endl;
    std::cout << "short is integral? " << is_integral<short>::value << std::endl;
    std::cout << "int is integral? " << is_integral<int>::value << std::endl;
    std::cout << "long is integral? " << is_integral<long>::value << std::endl;
    std::cout << "long long is integral? " << is_integral<long long>::value << std::endl;
    
    std::cout << "float is integral? " << is_integral<float>::value << std::endl;
    std::cout << "double is integral? " << is_integral<double>::value << std::endl;
    
    
    return 0;
}
