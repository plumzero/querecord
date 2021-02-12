
#include <iostream>
#include <type_traits>

enum Week {
    Sunday = 0,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

enum class Month : int {
    Jan = 1,
    Feb,
    Mar,
    Apr,
    May,
    Jun,
    Jul,
    Aug,
    Sep,
    Oct,
    Nov,
    Dec
};

template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

int main()
{    
    std::cout << std::boolalpha;

    std::cout << "C 式枚举测试" << std::endl;
    std::cout << "is enum? " << std::is_enum<Week>::value << std::endl;
    std::cout << "is integral? " << std::is_integral<Week>::value << std::endl;
    std::cout << "enum as same as int? " << std::is_same<Week, int>::value << std::endl;
    
    std::cout << "C++11 枚举类测试" << std::endl;
    std::cout << "is enum class? " << std::is_enum<Month>::value << std::endl;
    std::cout << "is integral? " << std::is_integral<Month>::value << std::endl;
    std::cout << "enum class as same as int? " << std::is_same<Month, int>::value << std::endl;

    int wd = Tuesday;
    // int md = Month::Mar; // compile error
    
    std::cout << Month::Jan << std::endl;

    return 0;
}