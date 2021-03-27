
#include <iostream>
#include <valarray>
#include <algorithm>
#include <iterator>

int main()
{
    // resize size
    {
        std::valarray<double> data(15);
        
        data.resize(50, 1.5);
        
        std::cout << "size=" << data.size() << std::endl;
    }
    
    // swap
    {
        std::valarray<size_t> sizes_3 { 1, 2, 3 };
        std::valarray<size_t> sizes_4 { 2, 3, 4, 5 };
        
        sizes_3.swap(sizes_4);
        
    }
    
    // min max average
    {
        std::valarray<size_t> vals { 2, 37, 14, 25 };
        
        std::cout << "min=" << vals.min() << ", max=" << vals.max() << std::endl;
        std::cout << "average=" << vals.sum() / vals.size() << std::endl;
    }
    
    // std::begin std::end
    {
        std::valarray<size_t> vals { 2, 37, 14, 25 };
        
        for (auto it = std::begin(vals); it != std::end(vals); it++) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    
    // shift
    {
        std::valarray<int> d1 { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        
        auto d2 = d1.shift(2);
        
        std::copy(std::begin(d2), std::end(d2), std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl;
        
        auto d3 = d1.shift(-3);
        std::copy(std::begin(d3), std::end(d3), std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl;
    }

    // cshift
    {
        std::valarray<int> d1 { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        
        auto d2 = d1.cshift(2);
        
        std::copy(std::begin(d2), std::end(d2), std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl;
        
        auto d3 = d1.cshift(-3);
        std::copy(std::begin(d3), std::end(d3), std::ostream_iterator<int>{ std::cout, " " });
        std::cout << std::endl;
    }
    
    // apply
    {
        std::valarray<double> time { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
        
        std::valarray<double> distances = time.apply([](double t) -> double {
            const static double g{ 32.0 };
            return 0.5 * g * t * t;
        });
        
        std::copy(std::begin(distances), std::end(distances),
                  std::ostream_iterator<double>{ std::cout, " " });
        std::cout << std::endl;
    }
    
    // cmath
    {
        std::valarray<int> foo { 5, 3, -10, 4, -7 };
        std::valarray<int> bar = abs(foo);

        std::copy(std::begin(bar), std::end(bar),
                  std::ostream_iterator<double>{ std::cout, " " });
        std::cout << std::endl;
    }
    
    return 0;
}