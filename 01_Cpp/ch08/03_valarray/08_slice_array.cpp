
#include <iostream>
#include <valarray>
#include <algorithm>
#include <iterator>

int main()
{
    
    // slice_array 代理
    {
        std::valarray<int> data { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
        std::valarray<int> more { 2, 2, 3, 3, 3, 4, 4, 4, 4,  5,  5,  5,  5,  5,  6 };
        
        data[std::slice{0, 5, 1}] = 99;
        // 右操作数是 valarray 或 slice_array 时，必须保存它至少包含和左操作数一样多的元素(这里是 5 个)
        data[std::slice{10, 5, 1}] = more;
        
        std::copy(std::begin(data), std::end(data), std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl;
    }
    
    // 运算符: +
    {
        std::valarray<int> data { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
        
        std::slice_array<int> d_slice = data[std::slice{ 2, 3, 5 }];
        
        // 3+10 8+20 13+30
        d_slice += std::valarray<int>{ 10, 20, 30 };
    
        std::copy(std::begin(data), std::end(data), std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl; 
    }
    
    // 运算符: ×
    {
        std::valarray<int> data { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
        
        std::slice_array<int> d_slice = data[std::slice{ 0, 3, 5 }];
        
        // 1*22 6*17 11*10
        d_slice *= std::valarray<int>{ 22, 17, 10 };
    
        std::copy(std::begin(data), std::end(data), std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl; 
    }
    
    // 局部运算: 最后一行乘以 3
    {
        std::valarray<int> data {  1,  2,  3,  4,  5,
                                   6,  7,  8,  9, 10,
                                  11, 12, 13, 14, 15 };
        
        std::slice row3{ 10, 5, 1 };

        data[row3] *= std::valarray<int>(3, row3.size());
    
        std::copy(std::begin(data), std::end(data), std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl; 
    }
    
    // 局部运算: 第 5 列元素加到第 2 和第 4 列上
    {
        std::valarray<int> data {  1,  2,  3,
                                   4,  5,  6, 
                                   7,  8,  9,
                                  10, 11, 12,
                                  13, 14, 15 };
        
        std::valarray<int> col5 { data[std::slice{4, 3, 5}] };
        
        data[std::slice{1, 3, 5}] += col5;
        data[std::slice{3, 3, 5}] += col5;
    
        std::copy(std::begin(data), std::end(data), std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl; 
    }
    
    return 0;
}