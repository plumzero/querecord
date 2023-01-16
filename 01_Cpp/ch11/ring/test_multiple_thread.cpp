
#include "ring.h"
#include <thread>
#include <chrono>
#include <atomic>
#include <algorithm>

#define SIZE 10

int main()
{
    RingQueue<int> queue{102400};
    std::atomic<size_t> cnter{0};

    std::vector<std::thread> read_vec;
    for (int i = 0; i < SIZE; i++) {
        std::thread th = std::thread([&queue](){
            for (int j = 0; j < 204800; j++) {
                queue.Put(j);
            }
        });
        read_vec.emplace_back(std::move(th));
    }
    std::for_each(read_vec.begin(), read_vec.end(), std::mem_fn(&std::thread::detach));

    size_t arr[SIZE] = {0};

    std::vector<std::thread> write_vec;
    for (int i = 0; i < SIZE; i++) {
        std::thread th = std::thread([&queue, &cnter, &arr, i](){
            while (true) {
                // int x;
                // queue.Take(x);
                // ++cnter;
                std::vector<int> lst;
                queue.Take(lst);
                cnter += lst.size();
                ++arr[i];
            }
        });
        write_vec.emplace_back(std::move(th));
    }
    std::for_each(write_vec.begin(), write_vec.end(), std::mem_fn(&std::thread::detach));

    std::cout << "wait for 10 seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "cnter=" << cnter << std::endl;
    size_t sum = 0;
    for (size_t i = 0; i < SIZE; i++) {
        std::cout << i << ": " << arr[i] << std::endl;
        sum += arr[i];
    }
    std::cout << "sum=" << sum << std::endl;
    std::cout << "q.size=" << queue.Size() << std::endl;
    queue.Print();

    return 0;
}