
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <cassert>

template <class T>
struct less
{
    bool operator()(const T& x, const T& y) const { return x < y; }
};

int main()
{
    {
        std::list<int> des_values { 2, 4, 6, 14 };
        std::list<int> src_values { -2, 1, 7, 10 };
        
        des_values.merge(src_values);
        
        assert(src_values.empty());
        
        std::cout << des_values.size() << std::endl;
        std::ostream_iterator<int> oit(std::cout, " ");
        std::copy(des_values.begin(), des_values.end(), oit);
        std::cout << std::endl;
    }
    
    {
        std::list<std::string> des_strs { "three", "six", "eight" };
        std::list<std::string> src_strs { "seven", "four", "nine" };
        
        des_strs.sort(less<std::string>());
        src_strs.sort(less<std::string>());
        
        des_strs.merge(src_strs, less<std::string>());
        
        std::cout << des_strs.size() << std::endl;
        std::ostream_iterator<std::string> oit(std::cout, " ");
        std::copy(des_strs.begin(), des_strs.end(), oit);
        std::cout << std::endl;
    }
    
    return 0;
}