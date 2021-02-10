
#include <functional>
#include <string>
#include <iostream>

template<typename T>
inline void hash_combine(size_t& seed, const T& val)
{
    seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

/** 可变参数模板函数声明 */
template<typename... Types>
inline size_t hash_val(const Types&... args);

/** 递归展开方式 */
template<typename T, typename... Types>
inline void hash_val(size_t& seed, const T& val, const Types&... args)
{
    hash_combine(seed, val);
    hash_val(seed, args...);
}

/** 递归终止条件 */
template<typename T>
inline void hash_val(size_t& seed, const T& val)
{
    hash_combine(seed, val);
}

/** 可变参数模板函数定义 */
template<typename... Types>
inline size_t hash_val(const Types&... args)
{
    size_t seed = 0;
    hash_val(seed, args...);

    return seed;
}

class Customer
{
public:
    Customer(const std::string& f, const std::string& l, int n) : fname(f), lname(l), no(n) {}
    ~Customer(){}

    std::string fname;
    std::string lname;
    int no;
};

class CustomerHash
{
public:
    std::size_t operator()(const Customer& c) const
    {
        return hash_val(c.fname, c.lname, c.no);
    }
};

int main()
{
    Customer c1("Hello", "World", 1);
    std::cout << CustomerHash()(c1) << std::endl;
    
    Customer c2("Hello", "World", 2);
    std::cout << CustomerHash()(c2) << std::endl;
    
    Customer c3("World", "Hello", 2);
    std::cout << CustomerHash()(c3) << std::endl;
    
    return 0;
}