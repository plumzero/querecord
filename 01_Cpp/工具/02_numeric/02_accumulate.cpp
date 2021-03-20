
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <functional>
#include <numeric>

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
    // 忽略 3 以下的
    {
        std::vector<int> values { 2, 0, 12, 3, 5, 0, 2, 7, 0, 8 };
        int min { 3 };
        auto sum = std::accumulate(std::begin(values), std::end(values), 0, [min](int sum, int v){
            if (v < min)
                return sum;
            return sum + v;
        });
        
        std::cout << "The sum of the elements greater or equal than " << min << " is " << sum << std::endl;
    }
    
    // 相乘
    {
        std::vector<int> values { 2, 3, 5, 7, 11, 13 };
        auto product = std::accumulate(std::begin(values), std::end(values), 1, std::multiplies<int>());
        
        std::cout << "The product is " << product << std::endl;
    }
    
	// 自定义累积
    {
        std::vector<Str> v;
        
        Str s1{"Hello"};
        Str s2{"World"};

        v.push_back(s1);
        v.push_back(s2);

        std::string s = std::accumulate(v.begin(), v.end(), Str(""));
        
        std::cout << s << std::endl;        
    }
        
    return 0;
}
