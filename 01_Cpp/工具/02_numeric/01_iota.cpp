
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>

#include <numeric>

int main()
{
    std::vector<double> data(9);
    double initial { -4 };
    
    std::iota(std::begin(data), std::end(data), initial);
    
    std::copy(std::begin(data), std::end(data),
              std::ostream_iterator<double>(std::cout << std::fixed
                    << std::setprecision(1), " "));
                    
    std::cout << std::endl;
    
    return 0;
}