
#include <chrono>
#include <iostream>

int main()
{
    // 浮点
    {
        std::chrono::duration<double, std::ratio<1, 5>> d1 { 50 };  // 10 seconds
        std::chrono::duration<double, std::ratio<1, 3>> d2 { 45 };  // 15 seconds
        
        d1 += d2;
        
        std::cout << "float: d1 = " << d1.count() << std::endl;
    }
    
    // 整型
    {
        std::chrono::duration<int, std::ratio<1, 5>> d1 { 50 };  // 10 seconds
        std::chrono::duration<int, std::ratio<1,10>> d2 { 50 };  //  5 seconds
        std::chrono::duration<int, std::ratio<1, 3>> d3 { 45 };  // 15 seconds
        std::chrono::duration<int, std::ratio<1, 6>> d4 { 60 };  // 10 seconds
        
        // d1 += d2;   // Won't compiled
        d2 += d1;      // OK
        // d3 += d4;   // Won't compiled
        d4 += d3;      // OK
        
        std::cout << "integer: d2 = " << d2.count() << ", d4 = " << d4.count() << std::endl;
    }
    
    // duration_cast
    {
        std::chrono::duration<int, std::ratio<1, 5>> d1 { 50 };  // 10 seconds
        std::chrono::duration<int, std::ratio<1,10>> d2 { 50 };  //  5 seconds
        std::chrono::duration<int, std::ratio<1, 3>> d3 { 45 };  // 15 seconds
        std::chrono::duration<int, std::ratio<1, 6>> d4 { 60 };  // 10 seconds
        
        d1 += std::chrono::duration_cast<std::chrono::duration<int, std::ratio<1, 5>>> (d2);
        std::cout << "duration_cast: d1 = " << d1.count() << std::endl;
        
        d3 += std::chrono::duration_cast<std::chrono::duration<int, std::ratio<1, 3>>> (d4);
        std::cout << "duration_cast: d3 = " << d1.count() << std::endl;
    }
    
    // assignment
    {
        std::chrono::duration<int, std::ratio<1, 5>> d1 { 50 };
        std::chrono::duration<int, std::ratio<1,10>> d2 { 53 };
        
        d2 = d1;
        
        std::cout << "d1 = " << d2.count() << std::endl;
    }
    
    return 0;
}