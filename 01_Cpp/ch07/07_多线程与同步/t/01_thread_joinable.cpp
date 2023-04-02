#include <iostream>
#include <thread>
#include <chrono>

void foo() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
    std::thread th;
    std::cout << "before starting, joinable: " << std::boolalpha << th.joinable() << std::endl;
    
    th = std::thread(foo);
    std::cout << "after starting, joinable: " << th.joinable() << std::endl;
    
    th.join();
    std::cout << "after joining, joinable: " << th.joinable() << std::endl;
    
    return 0;
}
