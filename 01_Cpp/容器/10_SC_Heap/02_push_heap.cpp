
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

int main ()
{
    {
        std::vector<double> v{ 2.5, 10, 3.5, 6.5, 8, 12, 1.5, 6 };
        
        std::make_heap(v.begin(),v.end());
        
        std::cout << "B before: ";
        std::ostream_iterator<double> oit_before(std::cout, " ");
        std::copy(v.begin(), v.end(), oit_before);
        std::cout << std::endl;
        
        v.push_back(11);
        std::push_heap(v.begin(), v.end());
        
        std::cout << "B  after: ";
        std::ostream_iterator<double> oit_after(std::cout, " ");
        std::copy(v.begin(), v.end(), oit_after);
        std::cout << std::endl;
    }
    
    {
        std::vector<double> v{ 2.5, 10, 3.5, 6.5, 8, 12, 1.5, 6 };
        
        std::make_heap(v.begin(),v.end(), std::greater<double>());
        
        std::cout << "S before: ";
        std::ostream_iterator<double> oit_before(std::cout, " ");
        std::copy(v.begin(), v.end(), oit_before);
        std::cout << std::endl;
        
        v.push_back(1.2);
        std::push_heap(v.begin(), v.end(), std::greater<double>());
        
        std::cout << "S  after: ";
        std::ostream_iterator<double> oit_after(std::cout, " ");
        std::copy(v.begin(), v.end(), oit_after);
        std::cout << std::endl;
    }
    
    return 0;
}