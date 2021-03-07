
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
    {
        auto my_tuple = std::make_tuple(Name{"Peter", "Piper"}, 42, std::string{"914 626 7890"});
        
        Name name{};
        size_t age{};
        std::string phone{};
        
        std::tie(name, age, phone) = my_tuple;
        
        std::cout << name.firstname << "." << name.lastname
                  << " age=" << age << " tel:" << phone << std::endl;
    }
    
    // 忽略对某些元素的获取
    {
        auto my_tuple = std::make_tuple(Name{"Peter", "Piper"}, 42, std::string{"914 626 7890"});
        
        Name name{};
        std::string phone{};
        
        std::tie(name, std::ignore, phone) = my_tuple;
        
        std::cout << name.firstname << "." << name.lastname
                  << " tel:" << phone << std::endl;
    }
    
    return 0;
}