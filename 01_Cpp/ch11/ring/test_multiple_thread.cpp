
#include "ring.h"
#include <thread>
#include <chrono>
#include <atomic>
#include <algorithm>

#define SIZE 10

int main()
{
    RingQueue<int> queue{1024};
    std::atomic<size_t> cnter{0};

    std::vector<std::thread> th_vec;
    for (int i = 0; i < SIZE; i++) {
        std::thread th = std::thread([&queue](){
            for (int j = 0; j < 498275; j++) {
                queue.Put(j);
            }
        });
        th_vec.emplace_back(std::move(th));
    }

    size_t nums[SIZE] = {0};

    for (int i = 0; i < SIZE; i++) {
        std::thread th = std::thread([&queue, &cnter, &nums, i](){
            while (true) {
                // int x;
                // queue.Take(x);
                // ++cnter;
                std::vector<int> lst;
                queue.Take(lst);
                cnter += lst.size();
                ++nums[i];
            }
        });
        th_vec.emplace_back(std::move(th));
    }

    std::for_each(th_vec.begin(), th_vec.end(), std::mem_fn(&std::thread::detach));

    std::cout << "wait for 20 seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(20));
    std::cout << "cnter=" << cnter << std::endl;
    size_t sum = 0;
    for (size_t i = 0; i < SIZE; i++) {
        std::cout << i << ": " << nums[i] << std::endl;
        sum += nums[i];
    }
    std::cout << "sum=" << sum << std::endl;
    std::cout << "q.size=" << queue.Size() << std::endl;
    queue.Print();

    return 0;
}