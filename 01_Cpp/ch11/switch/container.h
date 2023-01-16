
#include <iostream>
#include <sstream>
#include <mutex>
#include <type_traits>
#include <atomic>
#include <vector>
#include <list>
#include <deque>

template <typename T, template<typename T, typename Alloc = std::allocator<T>> class __container,
          class = typename std::enable_if<std::is_same<__container<T>, std::vector<T>>::value ||
                                          std::is_same<__container<T>, std::list<T>>::value ||
                                          std::is_same<__container<T>, std::deque<T>>::value>::type>
class Container
{
    typedef typename std::iterator_traits<typename __container<T>::iterator>::value_type value_type;
    typedef typename __container<T>::size_type size_type;
    typedef typename __container<T>::iterator iterator;
    typedef typename __container<T>::const_iterator const_iterator;
    typedef typename __container<T>::reference reference;
    typedef typename __container<T>::const_reference const_reference;
protected:
    __container<T> _c;
public:
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
        std::lock_guard<std::mutex> locker(_mutex);
        return _container[_curr].front();
    }
};
