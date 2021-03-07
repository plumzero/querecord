
#include <iostream>
#include <tuple>
#include <string>
#include <cassert>

class Name
{
public:
    std::string firstname {};
    std::string lastname {};
public:
    Name(const std::string& fn, const std::string& sn)
        : firstname(fn), lastname(sn) {}
    Name() = default;
};

int main()
{   
    // make_tuple 创建 tuple 对象
    {
        auto my_tuple = std::make_tuple(Name{"Peter", "Piper"}, 42, std::string{"914 626 7890"});
        (void) my_tuple;
    }
    
    // 构造 tuple 对象
    {
        std::tuple<std::string, size_t> m_t1;       // Default initialization
        (void) m_t1;
        
        std::tuple<Name, std::string> my_t2{Name{"Andy", "Capp"}, std::string{"Programmer"}};
        std::tuple<Name, std::string> copy_my_t2{my_t2};    // Copy constructor
        (void) copy_my_t2;
        
        std::tuple<std::string, std::string> my_t3{"this", "that"}; // Implicit conversion
        (void) my_t3;
    }
    
    return 0;
}