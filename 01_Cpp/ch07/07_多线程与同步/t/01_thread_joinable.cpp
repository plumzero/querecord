#include <iostream>
#include <thread>
#include <chrono>

/**
 *
 * 可 joinable 的线程对象表示一个线程是可执行的。
 * 不可 joinable 的线程对象一般有 3 类：
 *  缺省构造的线程对象；
 *  被剥离的线程对象；
 *  调用 join 或 detach 方法的对象；
 */

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