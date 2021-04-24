
#include <cstdlib>
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

template <typename T> struct MessageQueue
{
public:
    template <typename U> void push(U &&arg) {
        std::unique_lock<std::mutex> guard(mtx);
        q.push(std::forward<U>(arg));
        cv.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [=]() { return !q.empty(); });

        T out = std::move(q.front());
        q.pop();

        return out;
    }

    bool tryPop(T &out, std::chrono::milliseconds timeout) {
        std::unique_lock<std::mutex> lock(mtx);
        if (!cv.wait_for(lock, timeout, [=]() { return !q.empty(); }))
            return false;

        out = std::move(q.front());
        q.pop();
        
        return true;
    }

private:
    std::queue<T> q;
    std::mutex mtx;
    std::condition_variable cv;
};

int main()
{
    MessageQueue<int> mq;
    
    std::thread producer([&mq]() {
        while (1) {
            mq.push(rand());
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    });
    
    
    std::thread consumer([&mq](){
        while (1) {
            int ele;
            if (mq.tryPop(ele, std::chrono::milliseconds(100))) {
                std::cout << "Message: " << ele << std::endl;
            }
        }
    });
    
    producer.join();
    consumer.join();
    
    return 0;
}