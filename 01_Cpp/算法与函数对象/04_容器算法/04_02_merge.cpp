
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>

int main()
{
    {
        std::vector<int> these { 2, 15, 4, 11, 6, 7 };
        std::vector<int> those { 5, 2, 3, 2, 14, 11, 6 };
        
        std::stable_sort(std::begin(these), std::end(these), std::greater<int>());
        std::stable_sort(std::begin(those), std::end(those), std::greater<int>());
        
        std::vector<int> result(these.size() + those.size() + 10);
        
        auto end_iter = std::merge(std::begin(these), std::end(these),
                                   std::begin(those), std::end(those),
                                   std::begin(result),
                                   std::greater<int>());
                                   
        std::copy(std::begin(result), end_iter, std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
    
    return 0;
}