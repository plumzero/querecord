
#include <iostream>
#include <type_traits>
#include <typeinfo>

int main()
{
    typedef std::conditional<true, int, float>::type A;                         // int
    typedef std::conditional<false, int, float>::type B;                        // float
    typedef std::conditional<std::is_integral<A>::value, long, int>::type C;    // long
    typedef std::conditional<std::is_integral<B>::value, long, int>::type D;    // int
    
    typedef std::conditional<(sizeof(long long) > sizeof(long double)), long long, long double>::type max_size_t;
    
    std::cout << typeid(max_size_t).name() << std::endl;
    
    return 0;
}