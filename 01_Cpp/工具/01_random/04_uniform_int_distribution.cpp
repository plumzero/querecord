
#include <iostream>
#include <iomanip>
#include <random>

int main()
{
    // 缺省构造函数
    {
        std::uniform_int_distribution<> d;  // Distribution over 0 to max for type int, include
        
        std::cout << "Range from 0 to "
                  << std::numeric_limits<std::uniform_int_distribution<>::result_type>::max()
                  << std::endl;
        
        std::cout << "Range from " << d.min() << " to " << d.max() << std::endl;
        std::cout << "Range from " << d.a() << " to " << d.b() << std::endl;
    }
    
    // 提供下界的构造函数
    {
        std::uniform_int_distribution<> d {500};
        std::cout << "Range from " << d.a() << " to " << d.b() << std::endl;
    }
    
    // 提供下界和上界的构造函数
    {
        std::uniform_int_distribution<> dist { -5L, 5L };
        std::cout << "Range from " << dist.a() << " to " << dist.b() << std::endl;
        
        std::random_device rd;
        std::default_random_engine rng{ rd() };
        
        for (size_t i = 0; i < 8; i++) {
            std::cout << std::setw(2) << dist(rng) << " ";
        }
        std::cout << std::endl;
    }
    
    // 调用 param() 改变均匀分布
    {
        std::uniform_int_distribution<> dist { 0, 6 };
        std::random_device rd;
        std::default_random_engine rng { rd() };
        
        for (size_t i = 0; i < 8; i++) {
            std::cout << std::setw(3) << dist(rng) << " ";
        }
        std::cout << std::endl;
        
        // Save old range and set new range
        auto old_range = dist.param();
        dist.param(std::uniform_int_distribution<>::param_type{ -10, 20 });
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