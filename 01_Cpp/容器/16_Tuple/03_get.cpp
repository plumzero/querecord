
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
    // 基于索引获取元素
    {
        auto t = std::make_tuple(Name{"Peter", "Piper"}, 42, std::string{"914 626 7890"});
        
        std::cout << std::get<0>(t).firstname << "." << std::get<0>(t).lastname
                  << " age=" << std::get<1>(t) << " tel:" << std::get<2>(t) << std::endl;
    }
    
    // 基于类型获取元素 uncompiled
    {
        // auto t = std::make_tuple(Name{"Peter", "Piper"}, 42, std::string{"914 626 7890"});
        
        // std::cout << std::get<Name>(t).firstname << "." << std::get<Name>(t).lastname
                  // << " age=" << std::get<int>(t) << " tel:" << std::get<std::string>(t) << std::endl;
    }

    return 0;
}