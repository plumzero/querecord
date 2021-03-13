
#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
#include <string>

#include <cassert>

int main()
{
    // 删除单个元素
    {
        std::set<int> numbers { 2, 4, 6, 8, 10, 12, 14 };
        auto iter = numbers.erase(++std::begin(numbers));
        (void) iter;
        
        auto n = numbers.erase(12);
        assert(n == 1);
        
        n = numbers.erase(13);
        assert(n == 0);
        
        std::copy(std::begin(numbers), std::end(numbers), std::ostream_iterator<int>(std::cout, " "));
        
        std::cout << std::endl;
    }
    
    // 删除一段元素
    {
        std::set<int> numbers { 2, 4, 6, 8, 10, 12, 14 };
        
        auto iter1 = std::begin(numbers);
        
        std::advance(iter1, 5);
        
        auto iter = numbers.erase(++std::begin(numbers), iter1);
        (void) iter;
        
        std::copy(std::begin(numbers), std::end(numbers), std::ostream_iterator<int>(std::cout, " "));
        
        std::cout << std::endl;
    }

    return 0;
}