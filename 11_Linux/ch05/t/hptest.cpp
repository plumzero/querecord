
#include "hpallocator.h"
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

// 还需要做的测试
// 1. 内存反复分配/释放
// 2. 复杂结构体的测试
// 3. 所有方法的测试

int main()
{
    std::vector<int64_t> vec1;
    vec1.reserve(8);

    getchar();

    std::vector<int64_t, hpallocator<int64_t>> vec;
    vec.reserve(8);

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);

    vec.pop_back();

    std::for_each(vec.begin(), vec.end(), PrintElements<int64_t>());

    getchar();

    return 0;
}