
#include <iostream>
#include <iomanip>
#include <chrono>

void fun()
{
    for (int i = 0; i < 10; i++) {
        
    }
}

int main()
{
    auto b = std::chrono::high_resolution_clock::now();
    
    /** 取消同步 C 和 C++ 的 I/O */
    std::ios_base::sync_with_stdio(false);
    
    fun();
    
    auto e = std::chrono::high_resolution_clock::now();
    
    double cost = std::chrono::duration_cast<std::chrono::nanoseconds>(e - b).count();
    
    cost *= 1e-6;
    
    std::cout << std::setprecision(9) << cost << " milliseconds" << std::endl;
    
    return 0;
}