 
#include <iostream>
#include <thread>

void foo() {
    int i, total = 50;
    for (i = 0; i < total; i++)
        std::cout << "foo: " << i << std::endl;
}

void bar(int x) {
    int i;
    for (i = 0; i < x; i++)
        std::cout << "bar: " << i << std::endl;
}

int main() {
    std::thread first(foo);
    std::thread second(bar, 40);
    
    std::cout << "main, foo and bar now execute concurrently...\n";
    
    // 同步线程
    first.join();
    second.join();
    
    std::cout << "foo and bar completed.\n";
    
    return 0;
}