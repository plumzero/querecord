
#include <iostream>
#include <future>
#include <chrono>
#include <thread>

/** 使用异步实现同步 */

int add(int a, int b)
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    return a + b;
}

/**
 * 1. 可以看到前两种方式本质上是一样的，区别在于是否设置超时；
 * 2. 事实上 std::future::get 方法本身就有 wait 的作用，所以也可以按照方式三实现；
 * 3. 不过，使用异步实现同步时，方式二是更推荐的写法。
 */

int main()
{
    {
        /** [1] 使用异步实现同步 方式一 */
        std::cout << "使用异步实现同步 方式一" << std::endl;
        std::future<decltype(add(0,0))> fut = std::async(std::launch::async, add, 1234, 4321);
        std::future_status status;
        do {
            status = fut.wait_for(std::chrono::milliseconds(1000));
            if (status == std::future_status::timeout) {
                std::cout << "timeout" << std::endl;
                continue;
            } else if (status == std::future_status::ready) {
                std::cout << "success" << std::endl;
            }
        } while (status != std::future_status::ready);
        
        auto x = fut.get();
        std::cout << "x=" << x << std::endl;
    }
    
    {
        /** [2] 使用异步实现同步 方式二 */
        std::cout << "使用异步实现同步 方式二" << std::endl;
        std::future<decltype(add(0,0))> fut = std::async(std::launch::async, add, 1234, 4321);
        fut.wait();
        auto x = fut.get();
        std::cout << "x=" << x << std::endl;
    }
    
    {
        /** [3] 使用异步实现同步 方式三 */
        std::cout << "使用异步实现同步 方式三" << std::endl;
        std::future<decltype(add(0,0))> fut = std::async(std::launch::async, add, 1234, 4321);
        auto x = fut.get();
        std::cout << "x=" << x << std::endl;
    }
    
    return 0;
}