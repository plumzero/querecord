
#include <iostream>
#include <random>

int main()
{
    // 标准正态分布
    {
        std::normal_distribution<> dist;    // mu:0 sigma:1
        
        std::random_device rd;
        std::default_random_engine rng{ rd() };
        
        std::cout << "Normally distributed values: " << dist(rng) << " " << dist(rng) << std::endl;
    }
    
    // 期望为 50.0, 标准差是 10.0
    {
        double mu {50.0}, sigma{10.0};
        std::normal_distribution<> norm { mu, sigma };
        
        std::random_device rd;
        std::default_random_engine rng{ rd() };
        
        std::cout << "Normally distributed values: " << norm(rng) << " " << norm(rng) << std::endl;
    }
    
    // 获取期望与方差
    {
        double mu {50.0}, sigma{10.0};
        std::normal_distribution<> norm { mu, sigma };
        
        std::random_device rd;
        std::default_random_engine rng{ rd() };
        
        std::cout << "mu: " << norm.mean() << " sigma: " << norm.stddev() << std::endl;
    }
    
    // 重置期望与方差
    {
        double mu {50.0}, sigma{10.0};
        std::normal_distribution<> norm { mu, sigma };
        
        auto params = norm.param();     // Get mean and standard deviation
        norm.param(std::normal_distribution<>::param_type { params.mean(), params.stddev() + 5.0 });
        
        std::cout << "mu: " << norm.mean() << " sigma: " << norm.stddev() << std::endl;
    }
    
    return 0;
}