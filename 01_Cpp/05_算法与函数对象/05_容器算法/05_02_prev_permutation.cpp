
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{   
    // default: <
    {
        std::vector<int> range { 4, 2, 3, 1 };
        
        // 产生最大排列
        for (auto iter = std::begin(range); iter != std::end(range) - 1; ++iter) {
            std::iter_swap(iter, std::max_element(iter, std::end(range)));
        }
        
        // 从最大排列开始，生成全排列
        do {
            std::copy(std::begin(range), std::end(range), std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
        } while (std::prev_permutation(std::begin(range), std::end(range)));
        
        std::cout << std::endl;
    }
    
    // own defined: >
    {
        std::vector<int> range { 4, 2, 3, 1 };
        
        // 产生最小排列
        for (auto iter = std::begin(range); iter != std::end(range) - 1; ++iter) {
            std::iter_swap(iter, std::min_element(iter, std::end(range)));
        }
        
        // 从最小排列开始，生成全排列
        do {
            std::copy(std::begin(range), std::end(range), std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
        } while (std::prev_permutation(std::begin(range), std::end(range), std::greater<int>()));
        
        std::cout << std::endl;
    }
    
    return 0;
}