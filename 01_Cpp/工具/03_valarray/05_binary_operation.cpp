
#include <iostream>
#include <valarray>
#include <algorithm>
#include <iterator>

int main()
{
    // 算术
    {
        std::valarray<int> even { 2, 4, 6, 8 };
        std::valarray<int> odd { 3, 5, 7, 9 };
        
        std::valarray<int> r1 = even + 2;
        std::copy(std::begin(r1), std::end(r1), std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl;
        
        std::valarray<int> r2 = 2 * r1 + odd;
        std::copy(std::begin(r2), std::end(r2), std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl;
        
        
        r1 += 2 * odd - 4 * (r2 - even);
        std::copy(std::begin(r1), std::end(r1), std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl;
    }
    
    // 移位
    {
        std::valarray<int> odd { 3, 5, 7, 9 };
        
        std::valarray<int> r1 = odd << 3;
        
        std::copy(std::begin(r1), std::end(r1), std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl;
    }
    
    // 比较
    {
        std::valarray<int> even { 2, 4, 6, 8 };
        std::valarray<int> odd { 3, 5, 7, 9 };
        
        std::valarray<bool> b1 = (even + 1 == odd);
        std::copy(std::begin(b1), std::end(b1),
                  std::ostream_iterator<bool>{ std::cout << std::boolalpha, " " });
        std::cout << std::endl;
        
        std::valarray<bool> b2 = (odd < 5) && (even + 3 != odd);
        std::copy(std::begin(b2), std::end(b2),
                  std::ostream_iterator<bool>{ std::cout << std::boolalpha, " " });
        std::cout << std::endl;
    }
    
    return 0;
}