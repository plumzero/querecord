
#include <list>
#include <vector>
#include <deque>

class TDConstructed {
    // 目标构造模板函数
    template<class T> TDConstructed(T first, T last) : l(first, last) {};
    
    std::list<int> l;

public:
    // 委派构造函数一
    TDConstructed(std::vector<short>& v) : TDConstructed(v.begin(), v.end()) {}
    // 委派构造函数二
    TDConstructed(std::deque<int>& d) : TDConstructed(d.begin(), d.end()) {}
};

int main()
{
    std::vector<short> vec{ 1, 2, 3, 4 };
    TDConstructed td(vec);

    return 0;
}