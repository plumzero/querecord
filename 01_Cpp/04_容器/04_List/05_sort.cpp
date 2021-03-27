
#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <iterator>

template <class T>
struct greater
{
    bool operator()(const T& x, const T& y) const { return x > y; }
};

int main()
{
    {
        std::list<std::string> names { "Jules", "Jim", "Janet", "Jane", "Hugo", "Hannah", "Ann", "Alan" };
        
        names.sort();
        
        std::cout << names.size() << std::endl;
        std::ostream_iterator<std::string> oit(std::cout, " ");
        std::copy(names.begin(), names.end(), oit);
        std::cout << std::endl;
    }
    
    {
        std::list<std::string> names { "Jules", "Jim", "Janet", "Jane", "Hugo", "Hannah", "Ann", "Alan" };
        
        names.sort(greater<std::string>());
        
        std::cout << names.size() << std::endl;
        std::ostream_iterator<std::string> oit(std::cout, " ");
        std::copy(names.begin(), names.end(), oit);
        std::cout << std::endl;
    }
    
    return 0;
}