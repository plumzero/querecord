
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

int main()
{
    // 使用缺省排序
    {
        std::vector<int> set1 { 1, 2, 3, 4, 5, 6 };
        std::vector<int> set2 { 4, 5, 6, 7, 8, 9 };
        
        std::vector<int> result;
        
        std::set_intersection(std::begin(set1), std::end(set1),
                              std::begin(set2), std::end(set2),
                              std::back_inserter(result));
                       
        std::copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
    
    // 使用自定义排序
    {
        std::set<int, std::greater<int>> set1 { 1, 2, 3, 4, 5, 6 };
        std::set<int, std::greater<int>> set2 { 4, 5, 6, 7, 8, 9 };
        
        std::set<int, std::greater<int>> result;
        
        std::set_intersection(std::begin(set1), std::end(set1),
                              std::begin(set2), std::end(set2),
                              std::inserter(result, std::begin(result)),
                              std::greater<int>());
                       
        std::copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    return 0;
}