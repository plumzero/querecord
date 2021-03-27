
#include <iostream>
#include <valarray>
#include <algorithm>
#include <iterator>

int main()
{
    // 一维数组切片
    {
        std::valarray<int> data { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
        
        std::valarray<int> part = data[std::slice(2, 3, 4)];
        
        std::copy(std::begin(part), std::end(part), std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl;
    }
    
    // 选择行切片
    {
        std::valarray<int> data {  1,  2,  3,  4,  5,
                                   6,  7,  8,  9, 10,
                                  11, 12, 13, 14, 15
                                };
        
        std::valarray<int> part = data[std::slice(5, 5, 1)];
        
        std::copy(std::begin(part), std::end(part), std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl;
    }
    
    // 选择列切片
    {
        std::valarray<int> data {  1,  2,  3,  4,  5,
                                   6,  7,  8,  9, 10,
                                  11, 12, 13, 14, 15
                                };
        
        std::valarray<int> part = data[std::slice(2, 3, 5)];
        
        std::copy(std::begin(part), std::end(part), std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl;
    }
    
    return 0;
}