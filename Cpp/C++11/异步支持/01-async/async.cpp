
#include <iostream>
#include <future>
#include <chrono>
#include <thread>

int add(int a, int b)
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    return a + b;
}

int main()
{
    /** 相比延迟策略，异步策略用的更多一些 */
    {
        /** [1] 异步策略 */
        std::cout << "异步策略测试:" << std::endl;
        std::future<decltype(add(0,0))> fut = std::async(std::launch::async, add, 1234, 4321);
        /** do something others */
        std::future_status status;
        do {
            status = fut.wait_for(std::chrono::milliseconds(1000));
            if (status == std::future_status::timeout) {
                std::cout << "timeout" << std::endl;
                continue;
            /** 准确来说，既然已经设置为异步策略，就不应该再检测是否处于 deferred 状态 */
            // } else if (status == std::future_status::deferred) {
                // std::cout << "deferred" << std::endl;
                // break;   /** 跳出循环，否则会永远进行下去 */
            } else if (status == std::future_status::ready) {
                std::cout << "success" << std::endl;
            }
        } while (status != std::future_status::ready);
        
        try {
            auto x = fut.get();
            std::cout << "x=" << x << std::endl;
        }
        catch (std::exception&) {
            std::cout << "exception caught" << std::endl;
        }
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    {
        /** [2] 延迟策略 */
        std::cout << "延迟策略测试:" << std::endl;
        std::future<int> fut = std::async(std::launch::deferred, [](int a, int b)
            -> decltype (a + b) {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            std::cout << "延迟执行: child thread print tag" << std::endl;
            return a + b;
        }, 2345, 5432);
        /** do something others */

        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "先执行: parent thread print tag" << std::endl;
        
        /** 不会执行异步函数，直到调用 std::future::wait 或 std::future::get */
        // fut.wait();
        std::cout << fut.get() << std::endl;
    }
    
    return 0;
}
