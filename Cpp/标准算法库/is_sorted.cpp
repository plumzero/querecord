
#include <iostream>
#include <algorithm>
#include <vector>

/**
 * is_sorted 用来判断某个序列是否是排好序(缺省时为严格弱排序)的。
 * is_sorted_until 则用来返回序列中前面已经排好序的部分序列。
 */

// is_sorted_until 缺省时遵循 严格弱排序

int main()
{
    std::vector<int> v = { 1, 2, 5, 7, 9, 4 };
    
    bool isSort = is_sorted(v.begin(), v.end());
    std::cout << std::boolalpha << "strict weak ordering: " << isSort << std::endl; 
    
    auto pos = is_sorted_until(v.begin(), v.end());
    for (auto it = v.begin(); it != pos; it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    return 0;
}