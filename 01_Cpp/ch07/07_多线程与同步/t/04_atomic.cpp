
#include <atomic>
#include <iostream>

// Hide atomic from the public header and allow easy change to regular int
// on platforms where the atomic might have a perf impact.
class CachedSize {
public:
    int Get() const { return size_.load(std::memory_order_relaxed); }
    void Set(int size) { size_.store(size, std::memory_order_relaxed); }

private:
    std::atomic<int> size_{0};
};

int main()
{
    CachedSize cache;
    cache.Set(10086);

    std::cout << cache.Get() << std::endl;
}