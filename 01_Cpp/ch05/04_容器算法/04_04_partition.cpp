
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    // partition
    {
        std::vector<int> numbers { 65, 75, 56, 48, 31, 28, 32, 29, 40, 41, 44, 50 };
        
        std::copy(std::begin(numbers), std::end(numbers),
                  std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;       
        
        std::partition(std::begin(numbers), std::end(numbers), [](int t){ return t % 2 == 0; });
        
        std::copy(std::begin(numbers), std::end(numbers),
                  std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl; 
    }
    
    // stable_partition
    {
        std::vector<int> numbers { 65, 75, 56, 48, 31, 28, 32, 29, 40, 41, 44, 50 };
        
        std::copy(std::begin(numbers), std::end(numbers),
                  std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;       
        
        std::stable_partition(std::begin(numbers), std::end(numbers), [](int t){ return t % 2 == 0; });
        
        std::copy(std::begin(numbers), std::end(numbers),
                  std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl; 
    }
    
    return 0;
}