
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

int main ()
{
    // 对大顶堆升序排序
    {
        std::vector<double> v{ 2.5, 10, 3.5, 6.5, 8, 12, 1.5, 6 };
        
        std::make_heap(v.begin(),v.end());
        
        std::cout << "heap sort before: ";
        std::ostream_iterator<double> oit_before(std::cout, " ");
        std::copy(v.begin(), v.end(), oit_before);
        std::cout << std::endl;
        
        std::sort_heap(v.begin(), v.end());
        
        std::cout << "heap sort after:  ";
        std::ostream_iterator<double> oit_after(std::cout, " ");
        std::copy(v.begin(), v.end(), oit_after);
        std::cout << std::endl;
    }
    
    // 对大顶堆降序排序
    {
        std::vector<double> v{ 2.5, 10, 3.5, 6.5, 8, 12, 1.5, 6 };
        
        std::make_heap(v.begin(),v.end(), std::greater<double>());
        
        std::cout << "heap sort before: ";
        std::ostream_iterator<double> oit_before(std::cout, " ");
        std::copy(v.begin(), v.end(), oit_before);
        std::cout << std::endl;
        
        std::sort_heap(v.begin(), v.end(), std::greater<double>());
        
        std::cout << "heap sort after:  ";
        std::ostream_iterator<double> oit_after(std::cout, " ");
        std::copy(v.begin(), v.end(), oit_after);
        std::cout << std::endl;
    }
    
    return 0;
}