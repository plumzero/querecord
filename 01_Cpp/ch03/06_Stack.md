
stack 容器适配器的模板参数有两个，第一个参数是存储对象的类型，第二个参数是底层容器的类型。其定义如下:

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
`stack<T>` 的底层容器默认是 `deque<T>` 容器。通过第二个模板类型参数，也可以使用其他底层容器，只要它们支持 back()、push_back()、pop_back()、empty()、size() 这些操作。

如使用 list 作为底层容器:
```c++
    std::stack<std::string, std::list<std::string>> list_stack;
```

[将cad格式文件转为json格式](06_Stack/01_cad2json.cpp)
