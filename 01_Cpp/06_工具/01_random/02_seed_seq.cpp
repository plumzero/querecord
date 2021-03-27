
#include <iostream>
#include <vector>
#include <random>
#include <iterator>
#include <algorithm>

int main()
{
    // seed_seq 构造
    {
        std::seed_seq seeds1;                   // Default object
        
        std::seed_seq seeds2 { 2, 3, 4, 5 };    // Create from simple integers
        
        std::vector<unsigned int> data { 25, 36, 49, 64 };
        std::seed_seq seeds3(std::begin(data), std::end(data));   // Create from a range of integers
        
        std::random_device rd{};
        std::seed_seq seeds4 { rd(), rd() };    // Create from non-deterministic integers
    }
    
    // 相同的生成值序列
    {
        std::seed_seq seeds;
        std::vector<unsigned int> numbers(10);
        
        seeds.generate(std::begin(numbers), std::end(numbers));
        
        std::copy(std::begin(numbers), std::end(numbers), std::ostream_iterator<unsigned int>(std::cout, " "));
        std::cout << std::endl;
    }
    
    // 不同的生成值序列
    {
        std::random_device rd{};
        std::seed_seq seeds{ rd(), rd() };
        std::vector<unsigned int> numbers(10);
        
        seeds.generate(std::begin(numbers), std::end(numbers));
        
        std::copy(std::begin(numbers), std::end(numbers), std::ostream_iterator<unsigned int>(std::cout, " "));
        std::cout << std::endl;
    }

    return 0;
}