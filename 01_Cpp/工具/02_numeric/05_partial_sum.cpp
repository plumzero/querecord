
#include <iostream>
#include <vector>
#include <iterator>
#include <functional>

#include <numeric>

int main()
{
    // 默认: 加法
    {
        std::vector<int> data { 2, 3, 5, 7, 11, 13, 17, 19 };
        
        std::cout << "Partial sums: ";
        std::partial_sum(std::begin(data), std::end(data),
                         std::ostream_iterator<int>{std::cout, " "});
        std::cout << std::endl;
    }
    
    // 自定义: 减法
    {
        std::vector<int> data { 2, 3, 5, 7, 11, 13, 17, 19 };
        
        std::cout << "Partial sums: ";
        std::partial_sum(std::begin(data), std::end(data),
                         std::ostream_iterator<int>{std::cout, " "},
                         std::minus<int>());
        std::cout << std::endl;
    }

    return 0;
}