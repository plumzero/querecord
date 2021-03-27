
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

int main()
{
    // 源上部分排序(缺省排序)
    {
        size_t count { 5 };
        std::vector<int> numbers { 22, 7, 93, 45, 19, 56, 88, 12, 8, 7, 15, 10 };
        
        std::partial_sort(std::begin(numbers), std::begin(numbers) + count, std::end(numbers));
        
        std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
        
        std::cout << std::endl;
    }

    // 源上部分排序(自定义规则)
    {
        size_t count { 5 };
        std::vector<int> numbers { 22, 7, 93, 45, 19, 56, 88, 12, 8, 7, 15, 10 };
        
        std::partial_sort(std::begin(numbers), std::begin(numbers) + count, std::end(numbers),
                          std::greater<int>());
        
        std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
        
        std::cout << std::endl;
    }
    
    // 源外部分排序
    {
        std::vector<int> numbers { 22, 7, 93, 45, 19, 56, 88, 12, 8, 7, 15, 10 };
        std::vector<int> result(5);
        
        std::partial_sort_copy(std::begin(numbers), std::end(numbers),
                               std::begin(result),  std::end(result));
        
        std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
        
        std::copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
    
    // 源外部分排序(自定义规则)
    {
        std::vector<int> numbers { 22, 7, 93, 45, 19, 56, 88, 12, 8, 7, 15, 10 };
        std::vector<int> result(5);
        
        std::partial_sort_copy(std::begin(numbers), std::end(numbers),
                               std::begin(result),  std::end(result),
                               std::greater<int>());
        
        std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
        
        std::copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
    
    
    return 0;
}