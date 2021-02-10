

#include <iostream>
#include <type_traits>

int main()
{
    std::cout << std::boolalpha;
    // 添加和移除 const
    std::cout << std::is_same<const int, int>::value << std::endl;
    std::cout << std::is_same<const int, std::add_const<int>::type>::value << std::endl;
    std::cout << std::is_same<int, std::remove_const<const int>::type>::value << std::endl;
    // 添加和移除左值引用
    std::cout << std::is_same<int&, int>::value << std::endl;
    std::cout << std::is_same<int&, std::add_lvalue_reference<int>::type>::value << std::endl;
    std::cout << std::is_same<int, std::remove_reference<int&>::type>::value << std::endl;
    // 添加和移除右值引用
    std::cout << std::is_same<int&&, int>::value << std::endl;
    std::cout << std::is_same<int&&, std::add_rvalue_reference<int>::type>::value << std::endl;
    std::cout << std::is_same<int, std::remove_reference<int&&>::type>::value << std::endl;
    // 添加和移除指针
    std::cout << std::is_same<int*, int>::value << std::endl;
    std::cout << std::is_same<int*, std::add_pointer<int>::type>::value << std::endl;
    std::cout << std::is_same<int, std::remove_pointer<int*>::type>::value << std::endl;
    // 移除数组的顶层维度
    std::cout << std::is_same<int, std::remove_extent<int[]>::type>::value << std::endl;
    std::cout << std::is_same<int[2], std::remove_extent<int[][2]>::type>::value << std::endl;
    std::cout << std::is_same<int[2][3], std::remove_extent<int[][2][3]>::type>::value << std::endl;
    // 移除数组的所有维度
    std::cout << std::is_same<int, std::remove_all_extents<int[][2][3]>::type>::value << std::endl;
    // 取公共类型
    typedef std::common_type<unsigned char, short, int>::type NumericType;
    std::cout << std::is_same<int, NumericType>::value << std::endl;
    
    return 0;
}