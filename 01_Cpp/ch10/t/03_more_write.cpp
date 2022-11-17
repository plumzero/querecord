
#include <thread>
#include <vector>
#include <iostream>
#include <algorithm>

// 定义两个独立的全局变量
volatile int _vi = 0;
int _i = 0;

// volatile 并不能保证是线程安全的

void incr()
{
    for (int k = 0; k < 10000; k++) {
        _i++;
        _vi++;
    }
}

int main()
{
    std::vector<std::thread> vec;
    for (int j = 0; j < 20; j++) {
        std::thread th = std::thread(incr);
        vec.emplace_back(std::move(th));
    }

    std::for_each(vec.begin(), vec.end(), std::mem_fn(&std::thread::join));

    std::cout << "_vi = " << _vi << std::endl;
    std::cout << "_i = " << _i << std::endl;

    return 0;
}