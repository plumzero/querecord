
#include <valarray>

int main()
{
    std::valarray<int> numbers(15);             // 15 elements with default initial values 0
    std::valarray<size_t> sizes { 1, 2, 3 };    // 3 elements with values 1 2 and 3
    std::valarray<size_t> copy_sizes { sizes }; // 3 elements with values 1 2 and 3
    std::valarray<double> values;               // Empty array
    std::valarray<double> data(3.14, 10);       // 10 elements with values 3.14
    
    int vals[]{ 2, 4, 6, 8, 10, 12, 14 };
    std::valarray<int> vals1 { vals, 5 };       // 5 elements from vals: 2 4 6 8 10
    std::valarray<int> vals2 { vals + 1, 4 };   // 4 elements form vals: 4 6 8 10
     
    return 0;
}