
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <vector>

template<typename T>
class RingQueue {
public:
    RingQueue(size_t cap) : _cap(cap) { _queue.resize(cap); }
    ~RingQueue() { _queue.clear(); }
    void Put(const T& x) {
        std::unique_lock<std::mutex> locker(_mutex);
        _not_full.wait(locker, [this]() { return _stop_flag || ! full(); });
        if (_stop_flag) {
            return ;
        }
        _queue[_tail] = x;
        _tail = (_tail + 1) % _cap;
        _not_empty.notify_one();
    }
    void Take(T& t) {
        std::unique_lock<std::mutex> locker(_mutex);
        _not_empty.wait(locker, [this]() { return _stop_flag || ! empty(); });
        if (_stop_flag) {
            return ;
        }
        t = _queue[_head];
        _head = (_head + 1) % _cap;
        _not_full.notify_one();
    }
    void Take(std::vector<T>& lst) {
        std::unique_lock<std::mutex> locker(_mutex);
        _not_empty.wait(locker, [this]() { return _stop_flag || ! empty(); });
        if (_stop_flag) {
            return;
        }
        lst.clear();
        for (size_t i = _head; i != _tail; i = (i + 1) % _cap) {
            _head = (_head + 1) % _cap;
            lst.emplace_back(std::move(_queue[i]));
        }
        _not_full.notify_one();
    }
    void Stop() {
        {
            std::lock_guard<std::mutex> locker(_mutex);
            _stop_flag = true;
        }
        _not_full.notify_all();
        _not_empty.notify_all();
    }
    size_t Size() {
        std::lock_guard<std::mutex> locker(_mutex);
        return (_tail + _cap - _head) % _cap;
    }
    size_t Capacity() {
        return _cap;
    }
    void Clear() {
        std::lock_guard<std::mutex> locker(_mutex);
        _queue.clear();
    }
    void Print() {
        std::lock_guard<std::mutex> locker(_mutex);
        std::cout << std::boolalpha;
        std::cout << "cap=" << _cap;
        std::cout << ",size=" << (_tail + _cap - _head) % _cap;
        std::cout << ",head=" << _head;
        std::cout << ",tail=" << _tail;
        std::cout << ",empty=" << empty();
        std::cout << ",full=" << full();
        for (size_t i = _head; i != _tail; i = (i + 1) % _cap) {
            std::cout << "," << _queue[i];
        }
        std::cout << std::endl;
    }

private:
    inline bool empty() { return _head == _tail; }
    inline bool full() { return _head == (_tail + 1) % _cap; }

private:
    std::vector<T> _queue;
    std::mutex _mutex;
    std::condition_variable _not_empty;
    std::condition_variable _not_full;
    bool _stop_flag = false;
    size_t _cap = 1024;
    size_t _head = 0;
    size_t _tail = 0;
};
