
#include <stdio.h>
#include <deque>
#include <iterator>
#include <stdexcept>

template<typename T, class C = std::deque<T>, size_t N = 1024>
class RingQueue
{
public:
    typedef typename C::value_type value_type;
    typedef typename C::size_type size_type;
    typedef typename C::iterator iterator;
    typedef typename C::const_iterator const_iterator;
    typedef typename C::reference reference;
    typedef typename C::const_reference const_reference;

public:
    C c;
    iterator cur;
    iterator rear;
    size_type sz;
    
public:    
    bool empty() const
    {
        return sz == 0;
    }
    bool full() const
    {
        return sz == c.size();
    }
    size_type size() const
    {
        return sz;
    }
    reference front()
    {
        return *cur;
    }
    const_reference front() const
    {
        return *cur;
    }
    reference back()
    {
        if (rear == c.begin()) {
            return *c.rbegin();
        } else {
            return *std::prev(rear);
        }
    }
    const_reference back() const
    {
        if (rear == c.begin()) {
            return *c.rbegin();
        } else {
            return *std::prev(rear);
        }   
    }
    void push(const value_type& x)
    {
        if (full()) {
			throw std::runtime_error("queue size too long");
        } else {
            *rear = x;
            rear++;
        }
        if (rear == c.end()) {
            rear = c.begin();
        }
        sz++;
    }
    void pop()
    {
        if (empty()) {
            
        } else {
            cur++;
            sz--;
        }
        if (cur == c.end()) {
            cur = c.begin();
        }
    }
    
    RingQueue()
    {
        c.resize(N);
        cur = c.begin();
        rear = c.begin();
        sz = 0;
    }
    ~RingQueue(){}
};
