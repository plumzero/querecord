
### 堆栈 stack
```c++
    template <class T, class C = deque<T> > 
    class std::stack
    {
    protected:
        C c;
    public:
        typedef typename C::value_type value_type;
        typedef typename C::size_type size_type;
        typedef C container_type;
        
        explicit stack(const C& a = C()) : c(a) {}
        
        bool empty() const { return c.empty(); }
        size_type size() const { return c.size(); }
        
        value_type& top() { return c.back(); }
        const value_type& top() const { return c.back(); }
        
        void push(const value_type& x) { c.push_back(x); }
        void pop() { c.pop_back(); }
    };
```
堆栈也可以采用任何提供了 back()、push_back() 和 pop_back() 的序列作为保存自己元素的容器。