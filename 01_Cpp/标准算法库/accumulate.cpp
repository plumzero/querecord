
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

/**
 * accumulate() 函数适用于任何支持加法运算的序列，同样也适用于任何定义了 operator+() 函数的类对象。
 * 
 * 这里说明第2种 accumulate() 函数的用法。
 */

class Str
{
    std::string _s;
    
    friend Str operator+(const Str&, const Str&);
    
public:
    Str(const std::string& s) : _s(s) {}
    operator std::string() { return _s; }
};

Str operator+(const Str& lhs, const Str& rhs)
{
    return std::string().append(lhs._s).append(rhs._s);
}

int main()
{
    std::vector<Str> v;
    
    Str s1{"Hello"};
    Str s2{"World"};

    v.push_back(s1);
    v.push_back(s2);

    std::string s = std::accumulate(v.begin(), v.end(), Str(""));
    
    std::cout << s << std::endl;
        
    return 0;
}
