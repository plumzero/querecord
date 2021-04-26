
#include <iostream>
#include <iomanip>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <cassert>

using ULL = unsigned long long;

int main ()
{
    std::fstream iofs("finonacci.txt", std::fstream::out | std::fstream::binary);
    assert(iofs.is_open());
    
    ULL first {0}, second {1};
    
    auto iter = std::ostream_iterator<ULL>{ iofs, " " };
    
    (iter = first) = second;    // Write the first two values

    const size_t n {50};
    
    std::generate_n(iter, n, [&first, &second](){
        auto result = first + second;
        first = second;
        second = result;
        return result;
    });
    
    iofs.seekg(0);   // Reset to file begining
    std::for_each(std::istream_iterator<ULL>{iofs}, std::istream_iterator<ULL>{}, [](ULL k){
        const size_t perline { 6 };
        static size_t count {};
        std::cout << std::setw(12) << k << ((++count % perline) ? " " : "\n");
    });
    
    std::cout << std::endl;
    
    iofs.close();

    return 0;
}