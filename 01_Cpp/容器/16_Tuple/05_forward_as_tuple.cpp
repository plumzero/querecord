
#include <iostream>
#include <utility>
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

void changeName(std::tuple<Name&, Name&> names_pair)
{
    std::get<0>(names_pair).firstname = "Jim";
    std::get<0>(names_pair).lastname = "Green";
    
    std::get<1>(names_pair).firstname = "Bill";
    std::get<1>(names_pair).lastname = "Gates"; 
}

int main()
{
    {
        Name name1("Jack", "Jones");
        Name name2("Jill", "Smith");
        
        changeName(std::forward_as_tuple(name1, name2));
        
        std::cout << "name1: " << name1.firstname << "." << name1.lastname << std::endl;
        std::cout << "name2: " << name2.firstname << "." << name2.lastname << std::endl;
    }
    
    {
        std::pair<Name, Name> couple { std::piecewise_construct,
                                       std::forward_as_tuple("Jack", "Jones"),
                                       std::forward_as_tuple("Jill", "Smith") };
        
        std::cout << "first : " << couple.first.firstname << "." << couple.first.lastname << std::endl;
        std::cout << "second: " << couple.second.firstname << "." << couple.second.lastname << std::endl;   
    }
    
    return 0;
}