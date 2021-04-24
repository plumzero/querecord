
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
        
        auto iter = std::is_heap_until(v.begin(), v.end());
        assert(iter != v.end());
        std::cout << "values is a heap up to " << *iter << std::endl;
        
        std::push_heap(v.begin(), v.end());
        
        iter = std::is_heap_until(v.begin(), v.end());
        assert(iter == v.end());
        std::cout << "values is a heap totally" << std::endl;
    }
    
    {
        std::vector<double> v{ 2.5, 10, 3.5, 6.5, 8, 12, 1.5, 6 };
        
        std::make_heap(v.begin(),v.end(), std::greater<double>());

        std::pop_heap(v.begin(), v.end(), std::greater<double>());
        
        auto iter = std::is_heap_until(v.begin(), v.end(), std::greater<double>());
        assert(iter != v.end());
        std::cout << "values is a heap up to " << *iter << std::endl;
        
        std::push_heap(v.begin(), v.end(), std::greater<double>());
        
        iter = std::is_heap_until(v.begin(), v.end(), std::greater<double>());
        assert(iter == v.end());
        std::cout << "values is a heap totally" << std::endl;
    }

    return 0;
}