
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    {
        std::vector<int> range { 1, 2, 3, 4 };
        
        do {
            std::copy(std::begin(range), std::end(range), std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
        } while (std::next_permutation(std::begin(range), std::end(range)));
        
        std::cout << std::endl;
    }
    
    {
        std::vector<int> range { 4, 2, 3, 1 };
        
        do {
            std::copy(std::begin(range), std::end(range), std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
        } while (std::next_permutation(std::begin(range), std::end(range)));
        
        std::cout << std::endl;
    }

    return 0;
}