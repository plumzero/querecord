
#include <iostream>
#include <map>

int main()
{
    // 列表初始化 一
    {
        std::map<std::string, size_t> people {
            { "Ann", 25 },
            { "Bill", 46 },
            { "Jack", 32 },
            { "Jill", 32 }
        };
        
        (void) people;
    }
    
    // 列表初始化 二
    {
        std::map<std::string, size_t> people {
            std::make_pair("Ann", 25),
            std::make_pair("Bill", 46),
            std::make_pair("Jack", 32),
            std::make_pair("Jill", 32)
        };
        
        (void) people;
    }
    
    // 由其他容器初始化
    {
        std::map<std::string, size_t> people {
            std::make_pair("Ann", 25),
            std::make_pair("Bill", 46),
            std::make_pair("Jack", 32),
            std::make_pair("Jill", 32)
        };
        
        std::map<std::string, size_t> personnel { people };
        
        (void) personnel;
    }
    
    // 迭代器区间初始化
    {
        std::map<std::string, size_t> people {
            std::make_pair("Ann", 25),
            std::make_pair("Bill", 46),
            std::make_pair("Jack", 32),
            std::make_pair("Jill", 32)
        };
        
        std::map<std::string, size_t> personnel { std::begin(people), std::end(people) };
        
        (void) personnel;
    }
    
    return 0;
}