
#include <iostream>
#include <array>
#include <map>
#include <random>

int main()
{
    // 通过初始化列表指定权重
    {
        /**
         * 构造函数的初始化列表包含 6 个权值，因此分布只会生成 [0,6) 这个范围内的值。
         * 最后一个权值是其他权值的 3 倍，因此它出现的可能性是其他权值的 3 倍。
         */
        std::discrete_distribution<size_t> d { 1, 1, 1, 1, 1, 3 };  // weight at each index
        std::random_device rd;
        std::default_random_engine rng{ rd() };
        std::map<size_t, size_t> results;
        
        for (size_t go{}; go < 5000; ++go) {    // 5000 throws of the die
            ++results[d(rng)];
        }
        
        for (const auto & pr : results) {
            std::cout << "A " << (pr.first + 1) << " was thrown " << pr.second << " times" << std::endl;
        }
    }
    
    // 通过序列指定权重
    {
        std::array<double, 6> wts { 10.0, 10.0, 10.0, 10.0, 10.0, 30.0 };
        std::discrete_distribution<size_t> d{ std::begin(wts), std::end(wts) };
        std::random_device rd;
        std::default_random_engine rng{ rd() };
        std::array<std::string, 6> die_value { "one", "two", "three", "four", "five", "six" };
        std::map<size_t, size_t> results;
        
        for (size_t go{}; go < 5000; ++go) {
            ++results[d(rng)];
        }
        
        for (const auto & pr : results) {
            std::cout << "A " << die_value[pr.first] << " was throw " << pr.second << " times" << std::endl;
        }
    }
    
    return 0;
}