#include "myallocator.h"
#include <vector>
#include <algorithm>
#include <iostream>

template<typename _Tp>
struct PrintElements
{
    void operator()(const _Tp& t) const {
        std::cout << t << " ";
    }
};

int main()
{
    int elements[] = { 1, 2, 3, 4, 5 };
    const int n = sizeof(elements) / sizeof(int);

    std::vector<int, myallocator<int>> vec(elements, elements + n);
    std::for_each(vec.begin(), vec.end(), PrintElements<int>());

    return 0;
}