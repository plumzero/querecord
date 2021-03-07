
#include <iostream>
#include <map>
#include <string>

int main()
{
    {
        std::multimap<std::string, size_t> people {
            { "Ann", 35 },
            { "Bill", 46 },
            { "Jack", 77 },
            { "Jack", 32 },
            { "Jill", 32 },
            { "Ann", 25 }
        };
        
        std::string name{"Bill"};
        
        auto iter = people.find(name);
        if (iter != std::end(people)) {
            std::cout << name << " is " << iter->second << std::endl;
        }
        
        iter = people.find("Ann");
        if (iter != std::end(people)) {
            std::cout << iter->first << " is " << iter->second << std::endl;
        }
    }
    
    return 0;
}