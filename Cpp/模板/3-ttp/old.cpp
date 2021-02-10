
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>

template <typename T, typename C = std::vector<T>>
class X
{
    typedef typename C::value_type value_type;
    typedef typename C::size_type size_type;
    typedef typename C::iterator iterator;
    typedef typename C::const_iterator const_iterator;
    typedef typename C::reference reference;
    typedef typename C::const_reference const_reference;

protected:
    C c;
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
        X<int, std::vector<int>> x;
        
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
        X<double, std::list<double>> x;
        
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
        X<std::string, std::deque<std::string>> x;
        
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