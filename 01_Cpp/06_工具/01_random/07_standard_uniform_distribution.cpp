
#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <algorithm>
#include <random>

int main()
{
    // 随机位数为 12
    {
        std::vector<double> data(8);
        std::random_device rd;
        std::default_random_engine rng( rd() );
        
        // lambda 表达式会返回一个有 12 个随机比特的 double 类型的随机值，generate 会用这种数据来填充 data 中的元素
        std::generate(std::begin(data), std::end(data),
                      [&rng]{ return std::generate_canonical<double, 12>(rng); });
        
        std::copy(std::begin(data), std::end(data),
                  std::ostream_iterator<double>(std::cout << std::fixed << std::setprecision(4), " "));
        std::cout << std::endl;
    }
    
    // 增大随机位数，使更均匀
    {
        std::vector<long double> data;
        std::random_device rd;
        std::default_random_engine rng{ rd() };
        std::generate_n(std::back_inserter(data), 10,
                       [&rng]{ return std::generate_canonical<long double, std::numeric_limits<long double>::digits>(rng); });
        
        std::copy(std::begin(data), std::end(data),
                  std::ostream_iterator<double>(std::cout << std::fixed << std::setprecision(4), " "));
        std::cout << std::endl;
    }

    return 0;
}
