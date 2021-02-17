
### 队列 queue
```c++
    template <class T, class C = deque<T> >
    class std::queue
    {
    protected:
        C c;
    public:
        typedef typename C::value_type value_type;
        typedef typename C::size_type size_type;
        typedef C container_type;
        
        explicit queue(const C& a = C()) : c(a) {}
        
        bool empty() const { return c.empty(); }
        size_type size() const { return c.size(); }
        
        value_type& front() { return c.front(); }
        const value_type& front() const { return c.front(); }
        
        value_type& back() { return c.back(); }
        const value_type& back() const { return c.back(); }
        
        void push(const value_type& x) { c.push_back(x); }
        void pop() { c.pop_front(); }
    };
```
不同线程中请求程序和服务程序的消息同步处理：
```
    void server(queue<Message>& q, Lock& lck) {
        while (! q.empty()) {
            Message m;
            {
                LockPtr h(lck);         // 只在提取消息时掌握锁
                if (q.empty()) return;  // 其他程序取走了消息
                m = q.front();
                q.pop();
            }
            m.service();                // 调用为请求提供服务的函数
        }
    }
```