
#include <iostream>
#include <random>

int main()
{
    // 默认标准对数分布(期望为 0, 标准差为 1) 
    {
        std::lognormal_distribution<> dist;    // mu:0 sigma:1
        
        std::random_device rd;
        std::default_random_engine rng{ rd() };
        
        std::cout << "Normally logarithm distributed values: " << dist(rng) << " " << dist(rng) << std::endl;
    }
    
    // 期望为 5.0, 标准差是 0.5
    {
        double mu {5.0}, sigma{0.5};
        std::lognormal_distribution<> norm { mu, sigma };
        
        std::random_device rd;
        std::default_random_engine rng{ rd() };
        
        std::cout << "Normally logarithm distributed values: " << norm(rng) << " " << norm(rng) << std::endl;
    }
    
    // 获取期望与标准差
    {
        double mu {50.0}, sigma{10.0};
        std::lognormal_distribution<> norm { mu, sigma };
        
        std::random_device rd;
        std::default_random_engine rng{ rd() };
        
        std::cout << "mu: " << norm.m() << " sigma: " << norm.s() << std::endl;
    }
    
    // 重置期望与标准差
    {
        double mu {50.0}, sigma{10.0};
        std::lognormal_distribution<> norm { mu, sigma };
        
        auto params = norm.param();     // Get mean and standard deviation
        norm.param(std::lognormal_distribution<>::param_type { params.m(), params.s() + 5.0 });
        
        std::cout << "mu: " << norm.m() << " sigma: " << norm.s() << std::endl;
    }
    
    return 0;
}