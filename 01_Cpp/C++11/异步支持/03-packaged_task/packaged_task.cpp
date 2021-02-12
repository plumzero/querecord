
#include <iostream>
#include <future>
#include <chrono>
#include <thread>

/** 并无太大实用价值 */

int main ()
{
    std::packaged_task<int(int,int)> tsk([](int a, int b) -> decltype(a + b) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return a + b;
    });

    std::future<int> fut = tsk.get_future();
    
    std::thread th(std::move(tsk),10, 20);

    std::cout << fut.get() << std::endl;

    th.join();

    return 0;
}