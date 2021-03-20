
#include <iostream>
#include <vector>
#include <iterator>
#include <functional>

#include <algorithm>

int main()
{
    {
        std::vector<int> data { 2, 12, 3, 5, 17, -11, 113, 117, 19 };
        
        std::cout << "From values: ";
        std::copy(std::begin(data), std::end(data), std::ostream_iterator<int>{std::cout, " "});
        std::cout << std::endl;
        
        std::cout << "Min = " << *std::min_element(std::begin(data), std::end(data)) << std::endl;
        std::cout << "Max = " << *std::max_element(std::begin(data), std::end(data)) << std::endl;
    }
    
    {
        std::vector<int> data { 1, 2, 5, 7, 9, 4 };
        
        std::cout << "From values: ";
        std::copy(std::begin(data), std::end(data), std::ostream_iterator<int>{std::cout, " "});
        std::cout << std::endl;
        
        auto result = minmax_element(data.begin(), data.end());
        
        std::cout << "Min = " << *result.first << std::endl;
        std::cout << "Max = " << *result.second << std::endl;
    }

    return 0;
}