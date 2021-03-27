
#include <iostream>
#include <vector>
#include <iterator>
#include <functional>

#include <numeric>

int main()
{
    // 默认: 作减法
    {
        std::vector<int> data { 2, 3, 5, 7, 11, 13, 17, 19 };
        
        std::cout << "Differences: ";
        std::adjacent_difference(std::begin(data), std::end(data),
                                 std::ostream_iterator<int>{std::cout, " "});
        std::cout << std::endl;
    }
    
    // 自定义: 相邻乘法
    {
        std::vector<int> data { 2, 3, 5, 7, 11, 13, 17, 19 };
        
        std::cout << "Products: ";
        // result is: 2 6 15 35 77 143 221 323
        std::adjacent_difference(std::begin(data), std::end(data),
                                 std::ostream_iterator<int>{std::cout, " "},
                                 std::multiplies<int>());
        std::cout << std::endl;
    }
    
    // 计算 Fibonacci
    {
        std::vector<size_t> fib(15, 1);
        
        std::adjacent_difference(std::begin(fib), std::end(fib) - 1,
                                 std::begin(fib) + 1,
                                 std::plus<size_t>());
                                 
        std::copy(std::begin(fib), std::end(fib), std::ostream_iterator<size_t>{std::cout, " "});
        std::cout << std::endl;
    }

    return 0;
}