
#include <memory>
#include <type_traits>

#include <iostream>

namespace detail {
    template<bool B, typename T = void>
    using enable_if_t = typename std::enable_if<B,T>::type;

    /** 判断是否为动态数组 */
    template<typename T>
        struct is_unbounded_array_v : std::false_type {};
    template<typename T>
        struct is_unbounded_array_v<T[]> : std::true_type {};
     
    /** 判断是否为定长数组 */
    template<typename T>
        struct is_bounded_array_v : std::false_type{};
    template<typename T, std::size_t N>
        struct is_bounded_array_v<T[N]> : std::true_type{};
}

// 普通指针
template<class T, class... Args>
    detail::enable_if_t<!std::is_array<T>::value, std::unique_ptr<T>>
make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

// 动态数组
template<class T>
    detail::enable_if_t<detail::is_unbounded_array_v<T>::value, std::unique_ptr<T>>
make_unique(std::size_t n)
{
    typedef typename std::remove_extent<T>::type U;
    return std::unique_ptr<T>(new U[n]());
}

// 过滤掉定长数组情况
template<class T, class... Args>
    detail::enable_if_t<detail::is_bounded_array_v<T>::value>
make_unique(Args&&...) = delete;
  

struct Vec
{
    int x, y, z;
    Vec(int x = 0, int y = 0, int z = 0) noexcept : x(x), y(y), z(z) { }
    friend std::ostream& operator<<(std::ostream& os, const Vec& v)
    {
        return os << '{' << "x:" << v.x << " y:" << v.y << " z:" << v.z  << '}';
    }
};
  
int main()
{
    // 普通指针 - 使用默认构造函数
    std::unique_ptr<Vec> v1 = make_unique<Vec>();
    // 普通指针 - 使用匹配这些参数的构造函数
    std::unique_ptr<Vec> v2 = make_unique<Vec>(0, 1, 2);
    // 变长数组 - 创建指向 5 个元素数组的 unique_ptr 
    std::unique_ptr<Vec[]> v3 = make_unique<Vec[]>(5);
 
    std::cout << "make_unique<Vec>():      " << *v1 << std::endl
              << "make_unique<Vec>(0,1,2): " << *v2 << std::endl
              << "make_unique<Vec[]>(5):   " << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << "     " << v3[i] << '\n';
    }
    
    // 定长数组
    // std::unique_ptr<Vec> v4 = make_unique<Vec[10]>(0, 1, 2);  // 不支持
    
    return 0;
}