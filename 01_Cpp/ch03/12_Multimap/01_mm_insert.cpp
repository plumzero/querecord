
#include <iostream>
#include <map>
#include <string>

int main()
{
    // 元素方式插入
    {
        std::multimap<std::string, std::string> pets;
        
        auto iter = pets.insert(std::pair<std::string, std::string>{std::string{"dog"}, std::string{"Fang"}});
        
        iter = pets.insert(iter, std::make_pair("dog", "Sport"));
        
        pets.insert(std::make_pair("dog", "Rover"));
        pets.insert(std::make_pair("cat", "Korky"));
        
        pets.insert({
            {"rat", "Roland"},
            {"pig", "Pinky"},
            {"pig", "Perky"}
        });
        
        for (const auto & ele : pets) {
            std::cout << ele.first << "=>" << ele.second << std::endl;
        }
    }

    // 迭代器方式插入
    {
        // omit ...
    }
    
    return 0;
}