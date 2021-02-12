
#include <iostream>
#include <type_traits>
#include <memory>

template<class T>
struct Construct
{
    typedef typename std::remove_reference<T>::type U;      // 移除可能的引用
    Construct() : m_ptr(new U)
    {
    }
    typename std::add_lvalue_reference<U>::type
    Get() const
    {
        return *m_ptr.get();
    }
private:
    std::unique_ptr<U> m_ptr;
};

int main()
{
    Construct<int> c;
    int a = c.Get();
    std::cout << a << std::endl;
    
    return 0;
}