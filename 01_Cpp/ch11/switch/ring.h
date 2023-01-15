
#include <iostream>
#include <sstream>
#include <mutex>
#include <condition_variable>
#include <type_traits>
#include <atomic>
#include <vector>

template <typename T>
class RingQueue {
public:
    RingQueue(int cap) : _cap(cap), _stop_flag(false) {}
    void Put(const T &x) { Add(x); }
    
    void Take(std::list<T> &list) {
        std::unique_lock<std::mutex> locker(mutex_);
        _not_empty.wait(locker, [this]() { return _stop_flag || NotEmpty(); });
        if (_stop_flag) {
            return;
        }
        list.swap(queue_);
        _not_full.notify_one();
    }

    void Take(T &t) {
        std::unique_lock<std::mutex> locker(mutex_);
        _not_empty.wait(locker, [this] { return _stop_flag || NotEmpty(); });
        if (_stop_flag) {
            return;
        }
        t = _Q[_curr].front();
        _Q[_curr].pop_front();
        _not_full.notify_one();
    }

    void Stop() {
        {
            std::lock_guard<std::mutex> locker(mutex_);
            _stop_flag = true;
        }
        _not_full.notify_all();
        _not_empty.notify_all();
    }

    bool Empty() {
        std::lock_guard<std::mutex> locker(mutex_);
        return _Q[_curr].empty();
    }

    bool Full() {
        std::lock_guard<std::mutex> locker(mutex_);
        return _Q[_curr].size() == _cap;
    }

    size_t Size() {
        std::lock_guard<std::mutex> locker(mutex_);
        return _Q[_curr].size();
    }

    int Count() { return queue_.size(); }

    void Switch() {
        std::lock_guard<std::mutex> locker(mutex_);
        _curr = 1 - _curr;
        _next = 1 - _next;
        _head = 0;
        _tail = 0;
    }

private:
    bool NotFull() const {
        bool full = ((_tail + 1) % _cap == _head);
        return ! full;
    }

    bool NotEmpty() const {
        bool empty = (_head == _tail);
        return ! empty;
    }

    template <typename F>
    void Add(const F &x) {
        std::unique_lock<std::mutex> locker(mutex_);
        _not_full.wait(locker, [this]() { return _stop_flag || NotFull(); });
        if (_stop_flag) {
            return;
        }
        _Q[_curr].push_back(x);
        _not_empty.notify_one();
  }

private:
    std::vector<T> _Q[2];
    std::mutex mutex_;
    std::condition_variable _not_empty;
    std::condition_variable _not_full;
    size_t _cap;
    bool _stop_flag;
    size_t _curr = 0;
    size_t _next = 1;
    size_t _head = 0;
    size_t _tail = 0;
};

template <typename T>
class Ring
{
protected:
    std::vector<T> _c[2];
    size_t _cap = 1024;
    size_t _curr = 0;
    size_t _next = 1;
    size_t _head = 0;
    size_t _tail = 0;
    std::mutex _mutex;
public:
    Ring(size_t cap) { _cap = cap; _c.resize(_cap); }
    ~Ring() { _c.clear(); }
    void Print() {
        std::lock_guard<std::mutex> locker(_mutex);
        std::ostringstream oss; 
        oss << "curr=" << _curr << ",next=" << _next
            << ",c.size=" << _c[_curr].size()
            << ",n.size=" << _c[_next].size();
        std::cout << oss.str() << std::endl;
        return ;
    }
    void Switch() {
        std::lock_guard<std::mutex> locker(_mutex);
        _curr = 1 - _curr;
        _next = 1 - _next;
        return ;
    }
    bool IsEmpty() {
        return _head == _tail;
    }
    bool IsFull() {
        return (_tail + 1) % _cap == _head;
    }
    void Push(const T& val) {
        std::lock_guard<std::mutex> locker(_mutex);
        if (! IsFull()) (  
            _c[_curr][_ri++] = val;
        ) else {
            std::cout << "ring is full" << std::endl;
        }
    }

    const T 

    inline size_type size() const { return _c.size(); }
    inline void resize(size_type n) { return _c.resize(); }
    inline bool empty() const { return _c.empty(); }
    inline const_reference front() const { return _c.front(); }
    inline const_reference back() const { return _c.back(); }
    inline void pop_front() { return _c.pop_front(); }
    inline void pop_back() { return _c.pop_back(); }
    inline void push_front(const value_type& val) { return _c.push_front(val); }
    inline void push_back(const value_type& val) { return _c.push_back(val); }
};

template <typename T, template<typename T, typename Alloc = std::allocator<T>> class C>
class SwitchContainer
{
    typedef typename std::iterator_traits<typename C<T>::iterator>::value_type value_type;
    typedef typename C<T>::size_type size_type;
    typedef typename C<T>::iterator iterator;
    typedef typename C<T>::const_iterator const_iterator;
    typedef typename C<T>::reference reference;
    typedef typename C<T>::const_reference const_reference;
private:
    Container<T, C> _container[2];
    int _curr = 0;
    int _next = 1;
    std::mutex _mutex;
public:
    void Print() {
        std::lock_guard<std::mutex> locker(_mutex);
        std::ostringstream oss; 
        oss << "curr=" << _curr << ",next=" << _next
            << ",c.size=" << _container[_curr].size()
            << ",n.size=" << _container[_next].size();
        std::cout << oss.str() << std::endl;
        return ;
    }
    void Switch() {
        std::lock_guard<std::mutex> locker(_mutex);
        _curr = 1 - _curr;
        _next = 1 - _next;
        return ;
    }
    void PushBack(const value_type& val) {
        std::lock_guard<std::mutex> locker(_mutex);
        _container[_curr].push_back(val);
    }
    void PopFront() {
        std::lock_guard<std::mutex> locker(_mutex);
        _container[_curr].pop_front();
    }
    const_reference Front() const {

    }
};
