
#include <atomic>
#include <iostream>

class spin_mutex
{
public:
    spin_mutex() : _flag(ATOMIC_FLAG_INIT) {}

    void lock() {
        while (_flag.test_and_set(std::memory_order_acquire));
    }

    void unlock() { _flag.clear(std::memory_order_release); }

private:
    volatile std::atomic_flag _flag;
};

int main()
{
    spin_mutex mtx;

    return 0;
}