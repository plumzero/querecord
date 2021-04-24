
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>

/** C++11 模板模板参数 (template template parameter) */
template <typename T, template<typename T, typename Alloc = std::allocator<T>> class Container>
class X
{
    // 当然也可以写成 typedef typename Container<T>::value_type value_type;
    typedef typename std::iterator_traits<typename Container<T>::iterator>::value_type value_type;
    typedef typename Container<T>::size_type size_type;
    typedef typename Container<T>::iterator iterator;
    typedef typename Container<T>::const_iterator const_iterator;
    typedef typename Container<T>::reference reference;
    typedef typename Container<T>::const_reference const_reference;

protected:
    Container<T> c;
public:
    inline iterator insert(iterator position, const value_type& val)
    {
        return c.insert(position, val);
    }
    inline size_type size() const
    {
        return c.size();
    }
    inline iterator begin()
    {
        return c.begin();
    }
    inline const_iterator begin() const
    {
        return c.begin();
    }
    inline iterator end()
    {
        return c.end();
    }
    inline const_iterator end() const
    {
        return c.end();
    }
    inline bool empty() const
    {
        return c.empty();
    }
};

int main()
{
    {
        std::cout << "===== vector =====" << std::endl;
        X<int, std::vector> x;
        
        std::cout << std::boolalpha << "empty: " << x.empty() << std::endl;
        
        x.insert(x.end(), 1);
        x.insert(x.end(), 2);
        x.insert(x.end(), 3);
        
        std::cout << "size=" << x.size() << std::endl;
        std::cout << std::boolalpha << "empty: " << x.empty() << std::endl;
        for (const auto & ele : x) {
            std::cout << ele << " ";
        }
        std::cout << std::endl;
    }
    {
        std::cout << "===== list =====" << std::endl;
        X<double, std::list> x;
        
        std::cout << std::boolalpha << "empty: " << x.empty() << std::endl;
        
        x.insert(x.end(), 1.23);
        x.insert(x.end(), 4.56);
        x.insert(x.end(), 7.89);
        
        std::cout << "size=" << x.size() << std::endl;
        std::cout << std::boolalpha << "empty: " << x.empty() << std::endl;
        for (const auto & ele : x) {
            std::cout << ele << " ";
        }
        std::cout << std::endl;
    }
    
    {
        std::cout << "===== deque =====" << std::endl;
        X<std::string, std::deque> x;
        
        std::cout << std::boolalpha << "empty: " << x.empty() << std::endl;
        
        x.insert(x.end(), "Hello");
        x.insert(x.end(), "World");
        x.insert(x.end(), "Bye~");
        
        std::cout << "size=" << x.size() << std::endl;
        std::cout << std::boolalpha << "empty: " << x.empty() << std::endl;
        for (const auto & ele : x) {
            std::cout << ele << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}