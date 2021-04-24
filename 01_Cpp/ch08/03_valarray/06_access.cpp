
#include <iostream>
#include <valarray>
#include <algorithm>
#include <iterator>

int main()
{
    {
        std::valarray<int> data { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        
        data[1] = data[2] + data[3];
        data[3] *= 2;
        data[4] = ++data[5] - data[2];
        
        std::copy(std::begin(data), std::end(data), std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl;
    }
    
    return 0;
}