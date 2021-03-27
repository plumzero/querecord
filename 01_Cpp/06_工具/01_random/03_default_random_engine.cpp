
#include <iostream>
#include <vector>
#include <random>
#include <iterator>
#include <algorithm>

int main()
{
    // 缺省种子构造
    {
        std::default_random_engine rng;
    }
    
    // 种子为 10
    {
        std::default_random_engine rng{10};
    }
    
    // 传入随机数种子设备类
    {
        std::random_device rd;
        std::default_random_engine rng{ rd() };
    }
    
    // 通过 seed_seq 构造
    {
        std::seed_seq sd_seq { 2, 4, 6, 8 };
        std::default_random_engine rng{ sd_seq };
    }
    
    // 通过 seed_seq 构造
    {
        std::random_device rd;
        std::seed_seq sd_seq{ rd(), rd(), rd() };
        std::default_random_engine rng{ sd_seq };
    }
    
    return 0;
}