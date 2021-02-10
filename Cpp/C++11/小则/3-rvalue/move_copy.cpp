
#include <iostream>

    class A
    {
    public:
        A() : m_ptr(new int(0)) { std::cout << "construct" << std::endl; }
        A(const A& a) :m_ptr(new int(*a.m_ptr)) { std::cout << "copy(deep) construct" << std::endl; }
        A(A&& a) :m_ptr(a.m_ptr) { a.m_ptr = nullptr; std::cout << "move construct" << std::endl; }
        ~A() { std::cout << "destruct" << std::endl; delete m_ptr; }
    private:
        int* m_ptr;
    };

    A&& GetA() { return std::move(A()); }
    
    int main()
    {
        A&& a = GetA();
        
        return 0;
    }