
#include <iostream>
#include <vector>
#include <functional>

#include <numeric>

int main()
{
    // 计算积的和
    {
        std::vector<int> v1(5);
        std::vector<int> v2(5);
        
        std::iota(std::begin(v1), std::end(v1), 2);	// 2 3 4 5 6
        std::iota(std::begin(v2), std::end(v2), 3); // 3 4 5 6 7
        
		// 0 + (2 × 3) + (3 × 4) + (4 × 5) + (5 × 6) + (6 × 7)
        int result = std::inner_product(std::begin(v1), std::end(v1),
                                        std::begin(v2),
                                        0);
        std::cout << "Inner product is " << result << std::endl;
    }
    
    // 计算和的积
    {
        std::vector<int> v1(5);
        std::vector<int> v2(5);
        
        std::iota(std::begin(v1), std::end(v1), 2); // 2 3 4 5 6
        std::iota(std::begin(v2), std::end(v2), 3); // 3 4 5 6 7
        
        // 1 × (2 + 3) × (3 + 4) × (4 + 5) × (5 + 6) × (6 + 7)
        int result = std::inner_product(std::begin(v1), std::end(v1),
                                        std::begin(v2),
                                        1,
                                        std::multiplies<int>(), std::plus<int>());
        std::cout << "Inner product is " << result << std::endl;
    }
    
    // 位运算
    {
        std::vector<int> v1{ 100, 200, 300, 400, 500 };
        std::vector<int> v2{ 0xf, 0xf, 0xf, 255, 255 };
        
        // 0 + (100 & 0xf) + (200 & 0xf) + (300 & 0xf) + (400 & 255) + (500 & 255)
        int result = std::inner_product(std::begin(v1), std::end(v1),
                                        std::begin(v2),
                                        0,
                                        std::plus<int>(), std::bit_and<int>());
        std::cout << "Inner product is " << result << std::endl;
    }
    
    return 0;
}