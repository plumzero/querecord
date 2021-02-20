
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

int main ()
{
    {
        std::vector<double> v{ 2.5, 10, 3.5, 6.5, 8, 12, 1.5, 6 };
        
        std::make_heap(v.begin(),v.end());
        
        std::ostream_iterator<double> oit(std::cout, " ");
        std::copy(v.begin(), v.end(), oit);
        std::cout << std::endl;
    }
    
    {
        std::vector<double> v{ 2.5, 10, 3.5, 6.5, 8, 12, 1.5, 6 };
        
        std::make_heap(v.begin(),v.end(), std::greater<double>());
        
        std::ostream_iterator<double> oit(std::cout, " ");
        std::copy(v.begin(), v.end(), oit);
        std::cout << std::endl;
    }
    
    return 0;
}