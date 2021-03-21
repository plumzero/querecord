
#include <iostream>
#include <valarray>
#include <algorithm>
#include <iterator>

int main()
{
    // !
    {
        std::valarray<int> data { 2, 0, -2, 4, -4 };
        std::valarray<bool> result = !data;
        
        std::copy(std::begin(result), std::end(result),
                  std::ostream_iterator<bool>{ std::cout << std::boolalpha, " " });
        std::cout << std::endl;
    }
    
    // ~
    {
        std::valarray<int> data { 2, 0, -2, 4, -4 };
        std::valarray<int> result = ~data;
    
        std::copy(std::begin(result), std::end(result),
                  std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl; 
    }
    
    // -
    {
        std::valarray<int> data { 2, 0, -2, 4, -4 };
        std::valarray<int> result = -data;
    
        std::copy(std::begin(result), std::end(result),
                  std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl; 
    }
    
    return 0;
}