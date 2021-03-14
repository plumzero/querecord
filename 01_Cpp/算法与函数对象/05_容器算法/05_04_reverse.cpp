
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    // reverse
    {
        std::vector<int> numbers { 22, 7, 93, 45, 19, 56, 88, 12, 8, 7, 15, 10 };
        
        std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
        
        std::reverse(numbers.begin(), numbers.end());
        
        std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    // reverse_copy
    {
        std::vector<int> numbers { 22, 7, 93, 45, 19, 56, 88, 12, 8, 7, 15, 10 };
        
        std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
        
        std::reverse_copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }    

    return 0;
}