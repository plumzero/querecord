
#include <iostream>
#include <map>
#include <string>

int main()
{
    {
        std::multimap<std::string, std::string> pets;
        
        auto iter = pets.emplace("rabbit", "Flopsy");
        iter = pets.emplace_hint(iter, "rabbit", "Mopsy");
        
        for (const auto & ele : pets) {
            std::cout << ele.first << "=>" << ele.second << std::endl;
        }
    }
    
    return 0;
}