
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

        auto iterLower = people.lower_bound("Ann");
        auto iterUpper = people.upper_bound("Ann");
        if (iterLower != std::end(people)) {
            for (auto iter = iterLower; iter != iterUpper; iter++) {
                std::cout << iter->first << " is " << iter->second << std::endl;
            }
        }
    }
    
    return 0;
}