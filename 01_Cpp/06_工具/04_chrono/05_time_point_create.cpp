
#include <chrono>
#include <iostream>

int main()
{   
    // 利用 system_clock 创建 time_point
    {
        std::chrono::system_clock::time_point tp_sys1;              // Default object - the epoch
        std::chrono::time_point<std::chrono::system_clock> tp_sys2; // Default object - the epoch
    }
    
    // 利用 steady_clock 创建 time_point
    {
        std::chrono::steady_clock::time_point tp_steady1;
        std::chrono::time_point<std::chrono::steady_clock> tp_steady2;
    }
    
    // 利用 steady_clock 创建 time_point
    {
        std::chrono::high_resolution_clock::time_point tp_hrc1;
        std::chrono::time_point<std::chrono::high_resolution_clock> tp_hrc2;
    }
    
    return 0;
}