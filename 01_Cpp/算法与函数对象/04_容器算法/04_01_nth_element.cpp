
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

int main()
{
    // 缺省
    {
        size_t count { 5 };
        std::vector<int> numbers { 22, 7, 93, 45, 19, 56, 88, 12, 8, 7, 15, 10 };
        
        std::nth_element(std::begin(numbers), std::begin(numbers) + count, std::end(numbers));
        
        std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
        
        std::cout << std::endl;
    }

    // 自定义规则
    {
        size_t count { 5 };
        std::vector<int> numbers { 22, 7, 93, 45, 19, 56, 88, 12, 8, 7, 15, 10 };
        
        std::nth_element(std::begin(numbers), std::begin(numbers) + count, std::end(numbers),
                          std::greater<int>());
        
        std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
        
        std::cout << std::endl;
    }
    
    return 0;
}