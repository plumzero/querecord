
#include <iostream>
#include <map>
#include <string>
#include <memory>

using UPS = std::unique_ptr<std::string>;

class KeyCompare
{
public:
    bool operator() (const UPS& lhs, const UPS& rhs) const
    {
        return *lhs < *rhs;
    }
};

int main()
{
    std::map<UPS, std::string, KeyCompare> phonebook;
    
    phonebook.emplace(std::unique_ptr<std::string>(new std::string("Fred")), "914 626 7897");
    phonebook.insert(std::make_pair(std::unique_ptr<std::string>(new std::string("Lily")), "212 896 4337"));
    
    for (const auto & ele : phonebook) {
        std::cout << *ele.first << " " << ele.second << std::endl;
    }

    return 0;
}