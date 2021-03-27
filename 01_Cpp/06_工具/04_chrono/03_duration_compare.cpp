
#include <chrono>
#include <iostream>

int main()
{
    std::chrono::duration<int, std::ratio<1, 5>> d1 { 50 }; // 10 seconds
    std::chrono::duration<int, std::ratio<1,10>> d2 { 50 }; //  5 seconds
    std::chrono::duration<int, std::ratio<1, 3>> d3 { 45 }; // 15 seconds
    
    if ((d1 - d2) == (d3 - d1)) {
        std::cout << "both durations are "
                  << std::chrono::duration_cast<std::chrono::seconds>(d1 - d2).count()
                  << " seconds" << std::endl;  
    }
    
    return 0;
}