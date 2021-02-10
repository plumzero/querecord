
#include <vector>
#include <map>
#include <string>
#include <iostream>

/**
 * emplace_back 和 push_back 的比较
 * 
 * g++ -g emplace_back_diff.cpp -o emplace_back_diff -std=c++11 -fno-elide-constructors
 */

struct Complicated
{
    int year;
    double country;
    std::string name;
    
    Complicated(int a, double b, std::string c) : year(a), country(b), name(c)
    {
        std::cout << "is constructed" << std::endl;
    }
    
    Complicated(const Complicated& other)
        : year(other.year), country(other.country), name(std::move(other.name))
    {
        std::cout << "is moved" << std::endl;
    }
};

int main()
{
    std::map<int, Complicated> m;
    int anInt = 4;
    double aDouble = 5.0;
    std::string aString = "C++";
    std::cout << "-- insert --" << std::endl;
    m.insert(std::make_pair(4, Complicated(anInt, aDouble, aString)));
    
    std::cout << "-- emplace --" << std::endl;
    // should be easier for the optimizer
    m.emplace(4, Complicated(anInt, aDouble, aString));
    
    std::cout << "-- emplace_back --" << std::endl;
    std::vector<Complicated> v;
    v.emplace_back(anInt, aDouble, aString);
    
    std::cout << "-- push_back --" << std::endl;
    v.push_back(Complicated(anInt, aDouble, aString));

    return 0;
}