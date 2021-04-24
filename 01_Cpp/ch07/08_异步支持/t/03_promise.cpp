
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <thread>
#include <future>
#include <chrono>
#include <numeric>

int main ()
{
    {
        /** [1] promise 用法: 主线程向子线程供应数据 */
        std::cout << "promise 用法: 主线程向子线程供应数据:" << std::endl;
        std::promise<int> prom;

        std::future<int> fut = prom.get_future();   /** 设置 prom 与 fut 共享同一个 shared state */

        std::thread th1([](std::future<int>& fut) {
            auto x = fut.get(); /** I. block here until shared state ready */
            std::cout << "value: " << x << std::endl;
        }, std::ref(fut));                          /** 将 future 对象发送给新线程 */

        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        prom.set_value(10);     /** II. shared state ready! */

        th1.join();
    
    }
    
    {
        /** [2] promise 用法: 子线程向主线程供应数据 */
        std::cout << "promise 用法: 子线程向主线程供应数据:" << std::endl;
        std::promise<double> prom;
        std::future<double> fut = prom.get_future();
        
        std::vector<double> vec{ 1.234, 4,567, 26.32, 7.263, 8.23, 90.673};
        
        std::thread th1([](std::vector<double> vec, std::promise<double> calc_promise) {
            auto sum = std::accumulate(vec.begin(), vec.end(), 0.0f);
            calc_promise.set_value(sum);        /** II. shared state ready! */
        }, vec, std::move(prom));
        
        std::cout << fut.get() << std::endl;    /** I. block here until shared state ready */
        th1.join();
    }
    
    {
        /** [3] 模拟对发信号，实现线程间同步 */
        std::cout << "promise 用法: 模拟对发信号，实现线程间同步:" << std::endl;
        std::promise<void> barrier;
        std::future<void> barrier_future = barrier.get_future();
        
        std::thread th1([](std::promise<void> barrier) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            barrier.set_value();    /** II. shared state ready! */
        }, std::move(barrier));
        
        barrier_future.wait();      /** I. wait for shared state ready */
        
        th1.join();
    }

    return 0;
}