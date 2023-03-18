#include "atomicops.h"
#include <memory>
#include <atomic>
#include <thread>
#include <chrono>
#include <stdio.h>

// 在单线程中使用

int main()
{
    // std::thread([](){
    //     std::this_thread::sleep_for(std::chrono::seconds(1));
    //     sema->signal();
    // }).detach();

    std::atomic<int> cnter{0};
    std::unique_ptr<LightweightSemaphore> sema(new LightweightSemaphore());

    for (int i = 0; i < 100; i++) {
        if (cnter.load() > 0) {
            while (!sema->wait());
        }
        printf("===> %d\n", i);
        cnter++;
        sema->signal();
    }

    return 0;
}