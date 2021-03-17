
#include <iostream>
#include <iomanip>
#include <random>

int main()
{
    // 缺省构造函数
    {
        std::uniform_real_distribution<> values;  // Distribution over 0 to max for type int, include
        
        std::cout << "Range from " << values.min() << " to " << values.max() << std::endl;
        std::cout << "Range from " << values.a() << " to " << values.b() << std::endl;
    }
    
    // 提供下界和上界的构造函数
    {
        std::uniform_real_distribution<> values { 0.0, 10.0 };
        std::cout << "Range from " << values.a() << " to " << values.b() << std::endl;
        
        std::random_device rd;
        std::default_random_engine rng { rd() };
        
        for (size_t i = 0; i < 8; i++) {
            std::cout << std::fixed << std::setprecision(2)
                      << values(rng) << " ";
        }
        std::cout << std::endl;
    }
    
    // 调用 param() 改变均匀分布
    {
        std::uniform_real_distribution<> dist { 0.0, 6.0 };
        std::random_device rd;
        std::default_random_engine rng { rd() };
        
        for (size_t i = 0; i < 8; i++) {
            std::cout << std::setw(3) << dist(rng) << " ";
        }
        std::cout << std::endl;
        
        // Save old range and set new range
        auto old_range = dist.param();
        dist.param(std::uniform_real_distribution<>::param_type{ -10.0, 20.0 });
        for (size_t i = 0; i < 8; i++) {
            std::cout << std::setw(3) << dist(rng) << " ";
        }
        std::cout << std::endl;
        
        // Restore old range...
        dist.param(old_range);
        for (size_t i = 0; i < 8; i++) {
            std::cout << std::setw(3) << dist(rng) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}