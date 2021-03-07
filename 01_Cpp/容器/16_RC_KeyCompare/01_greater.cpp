
#include <iostream>
#include <map>

class Name
{
public:
    std::string firstname {};
    std::string lastname {};
public:
    Name(const std::string& fn, const std::string& sn)
        : firstname(fn), lastname(sn) {}
    Name() = default;
    
    // Greater-than operator
    bool operator>(const Name& name) const
    {
        return lastname > name.lastname || (lastname == name.lastname && firstname > name.firstname);
    }
};

int main()
{
    std::map<Name, size_t, std::greater<Name>> people {
        { Name{ "Al", "Bedo" }, 53 },
        { Name{ "Woody", "Leave" }, 33 },
        { Name{ "Noah", "Lot" }, 43 }
    };
    
    for (const auto & ele : people) {
        std::cout << ele.first.firstname << "." << ele.first.lastname << " " << ele.second << std::endl;
    }
    
    return 0;
}