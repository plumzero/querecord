
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <cassert>

int main ()
{
    {
        std::vector<double> v{ 2.5, 10, 3.5, 6.5, 8, 12, 1.5, 6 };
        
        std::make_heap(v.begin(),v.end());

        std::pop_heap(v.begin(), v.end());
        
        assert(! std::is_heap(v.begin(), v.end()));
        
        std::push_heap(v.begin(), v.end());
        
        assert(std::is_heap(v.begin(), v.end()));
        
        std::cout << "is_heap test success" << std::endl;
    }
    
    {
        std::vector<double> v{ 2.5, 10, 3.5, 6.5, 8, 12, 1.5, 6 };
        
        std::make_heap(v.begin(),v.end(), std::greater<double>());

        std::pop_heap(v.begin(), v.end(), std::greater<double>());
        
        assert(! std::is_heap(v.begin(), v.end(), std::greater<double>()));
        
        std::push_heap(v.begin(), v.end(), std::greater<double>());
        
        assert(std::is_heap(v.begin(), v.end(), std::greater<double>()));
        
        std::cout << "is_heap test success" << std::endl;
    }

    return 0;
}