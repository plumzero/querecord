
#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<int> srce { 1, 2, 3, 4 };
    std::deque<int> dest { 5, 6, 7, 8 };
    
    std::move(std::begin(srce), std::end(srce), std::back_inserter(dest));
    
    std::copy(std::begin(srce), std::end(srce), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    
    std::copy(std::begin(dest), std::end(dest), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    
    return 0;
}