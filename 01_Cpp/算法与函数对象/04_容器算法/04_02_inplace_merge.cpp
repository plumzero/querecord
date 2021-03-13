
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>

int main()
{
    {
        std::vector<int> these { 5, 17, 19, 20, 24, 30,
                                 9, 13, 19, 25, 29, 31, 40, 41
                               };
        
        std::inplace_merge(std::begin(these), std::begin(these) + 6, std::end(these));
                                   
        std::copy(std::begin(these), std::end(these), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
    
    return 0;
}