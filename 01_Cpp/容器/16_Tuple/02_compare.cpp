
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
    
    // Less-than operator
    bool operator<(const Name& name) const
    {
        return lastname < name.lastname || (lastname == name.lastname && firstname < name.firstname);
    }
};

int main()
{
    {
        auto tuple1 = std::make_tuple(Name{"Peter", "Piper"}, 42, std::string{"914 626 7890"});
        auto tuple2 = std::make_tuple(Name{"Jim", "Green"}, 12, std::string{"123 456 7890"});
        
        std::cout << std::boolalpha << (tuple1 < tuple2) << std::endl;
    }
    
    {
        auto t1 = std::make_tuple<std::string, std::string>("this", "that");
        auto t2 = std::make_tuple<std::string, std::string>("these", "those");
        
        std::cout << std::boolalpha << (t1 > t2) << std::endl;
    }

    return 0;
}