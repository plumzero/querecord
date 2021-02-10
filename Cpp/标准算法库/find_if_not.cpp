
#include <iostream>
#include <algorithm>
#include <vector>

/**
 * find_if_not 算法的含义和 find_if 是相反的，即查找不符合某个条件的元素，find_if 也可以
 * 实现 find_if_not 的功能，只需要将判断式改为否定的判断式即可
 */

int main()
{
    std::vector<int> v = { 1, 3, 5, 7, 9, 4 };
    auto isEven = [](int i){ return i % 2 == 0; };
    auto firstEven = std::find_if(v.begin(), v.end(), isEven);
    if (firstEven != v.end()) {
        std::cout << "the first even is " << *firstEven << std::endl;
    }
    
    // 用 find_if 来查找奇数则需要重新写一个否定含义的判断式
    auto isOdd = [](int i){ return i % 2 != 0; };
    auto firstOdd = std::find_if(v.begin(), v.end(), isOdd);
    if (firstOdd != v.end()) {
        std::cout << "the first odd is " << *firstOdd << std::endl;
    }
    
    // 用 find_if_not 来查找奇数则无须新定义判断式
    firstOdd = std::find_if_not(v.begin(), v.end(), isEven);
    if (firstOdd != v.end()) {
        std::cout << "the first odd is " << *firstOdd << std::endl;
    }
    
    return 0;
}