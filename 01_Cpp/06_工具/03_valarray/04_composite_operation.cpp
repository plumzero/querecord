
#include <iostream>
#include <valarray>
#include <algorithm>
#include <iterator>

int main()
{
    // 算术: += -= *= /= %=
    {
        std::valarray<int> v1 { 1, 2, 3, 4 };
        std::valarray<int> v2 { 3, 4, 3, 4 };
        
        v1 += 3;
        std::copy(std::begin(v1), std::end(v1),
                  std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl;
        
        v1 -= v2;
        std::copy(std::begin(v1), std::end(v1),
                  std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl;
    }
    
    
    // 位: &= |= ^=
    {
        std::valarray<int> v1 { 1, 2, 4, 8 };
        std::valarray<int> v2 { 4, 8, 16, 32 };
        
        v1 |= 4;
        std::copy(std::begin(v1), std::end(v1),
                  std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl;
        
        v1 &= v2;
        std::copy(std::begin(v1), std::end(v1),
                  std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl;
        
        v1 ^= v2;
        std::copy(std::begin(v1), std::end(v1),
                  std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl;
    }
    
    // 移位
    {
        std::valarray<int> v1 { 1, 2, 3, 4 };
        std::valarray<int> v2 { 4, 8, 16, 32 };
        
        v2 <<= v1;
        std::copy(std::begin(v2), std::end(v2),
                  std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl;
        
        v2 >>= 2;
        std::copy(std::begin(v2), std::end(v2),
                  std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl;
    }
    
    return 0;
}