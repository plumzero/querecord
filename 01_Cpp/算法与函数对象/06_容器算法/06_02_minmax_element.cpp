
#include <iostream>
#include <algorithm>
#include <vector>

/**
 * minmax_element 会将最小值和最大值的迭代器放到一个 pair 中返回。
 */

int main()
{
    std::vector<int> v = { 1, 2, 5, 7, 9, 4 };
    auto result = minmax_element(v.begin(), v.end());
    
    std::cout << "min: " << *result.first << std::endl;
    std::cout << "max: " << *result.second << std::endl;
    
    return 0;
}