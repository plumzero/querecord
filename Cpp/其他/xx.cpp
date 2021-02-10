// bitset::set
#include <iostream>       // std::cout
#include <bitset>         // std::bitset
#include <string>
#include <chrono>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <vector>
#include <unordered_map>

#define SIZE_FOR_TEST  100000

int main ()
{
    std::cout << "测试 bitset" << std::endl;
    
    std::bitset<4> foo(std::string("0001"));

    std::cout << foo << std::endl;

    std::cout << foo.set() << '\n';       // 1111
    std::cout << foo.set(2,0) << '\n';    // 1011
    std::cout << foo.set(2) << '\n';      // 1111
    
    std::cout << foo.reset() << "\n";


    // 测试时间 
    std::cout << "===== 测试时间 =====" << std::endl;

    int64_t chrono_now1 = std::chrono::system_clock().now().time_since_epoch().count();
    int64_t chrono_now2 = std::chrono::system_clock::now().time_since_epoch().count();
    int64_t chrono_now3 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    
    time_t time_now;
    time(&time_now);
    
    std::cout << "chrono_now1=" << chrono_now1 << std::endl;
    std::cout << "chrono_now2=" << chrono_now2 << std::endl;
    std::cout << "chrono_now3=" << chrono_now3 << std::endl;
    std::cout << "   time_now=" << time_now << std::endl;
    
    std::cout << "===== vector 和 unordered_map 的遍历测试 =====" << std::endl;
    std::vector<int> v;
    std::unordered_map<int, int> um;
    int count = 0;
        
    v.resize(SIZE_FOR_TEST);
    um.rehash(SIZE_FOR_TEST);

    um[1] = 10;
    um[2] = 20;
    um[6] = 80;
    um[7892] = 97302;

    for (auto it = um.begin(); it != um.end(); it++) {
        count++;
    }
    std::cout << "bucket_count=" << um.bucket_count() << ", count=" << count << std::endl;
    
    int64_t b, e;
    
    um.erase(6);
    
    count = 0;
    for (auto it = um.begin(); it != um.end(); it++) {
        count++;
    }
    std::cout << "bucket_count=" << um.bucket_count() << ", count=" << count << std::endl;
    
    count = 0;
    b = std::chrono::system_clock().now().time_since_epoch().count();
    for (auto it = v.begin(); it != v.end(); it++) {
        count++;
    }
    e = std::chrono::system_clock().now().time_since_epoch().count();
    std::cout << "vector: test " << count << " times spend " << e - b << " nanoseconds" << std::endl; 
    
    count = 0;
    b = std::chrono::system_clock().now().time_since_epoch().count();
    for (auto it = um.begin(); it != um.end(); it++) {
        count++;
    }
    e = std::chrono::system_clock().now().time_since_epoch().count();
    std::cout << "unordered_map: test " << count << " times spend " << e - b << " nanoseconds" << std::endl; 
    
    return 0;
}