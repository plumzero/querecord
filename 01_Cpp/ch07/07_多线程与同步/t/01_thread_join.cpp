
#include <iostream>
#include <thread>
#include <chrono>

void foo() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void bar() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void pause_thread(int n) {
    std::cout << "pause of " << n << " seconds begin..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(n));
    std::cout << "pause of " << n << " seconds ended" << std::endl;
}

int main() {
    std::cout << "Spawning 3 threads..." << std::endl;
    std::thread th1(pause_thread, 1);
    std::thread th2(pause_thread, 2);
    std::thread th3(pause_thread, 3);
    
    std::cout << "Done spawning threads. Now waiting for then to join:" << std::endl;
    th1.join();
    th2.join();
    th3.join();
    std::cout << "All threads joined!" << std::endl;
    
    // std::this_thread::sleep_for(std::chrono::seconds(5));    // 不可取
    
    return 0;
}