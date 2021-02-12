
/**
 *
 * 1.用法
 *   template<class T> struct decay;
 * 2.说明
 *   获取 T 的 decay 类型
 *   转换后的类型作为成员类型 decay::type 的别名
 *   T 的 decay 类型 左值表达式用作右值
 * 对 decay 的理解
 *   decay 腐朽，堕落回本原，应该是 T 最原始的的基类型
 */

#include <iostream>
#include <type_traits>

typedef std::decay<int>::type           A;      // int
typedef std::decay<int&>::type          B;      // int
typedef std::decay<int&&>::type         C;      // int
typedef std::decay<const int&>::type    D;      // int
typedef std::decay<int[2]>::type        E;      // int*
typedef std::decay<int(int)>::type      F;      // int(*)(int)

int main() {
    std::cout << std::boolalpha;
    std::cout << "typedefs of int: " << std::endl;
    std::cout << "A: " << std::is_same<int, A>::value << std::endl;
    std::cout << "B: " << std::is_same<int, B>::value << std::endl;
    std::cout << "C: " << std::is_same<int, C>::value << std::endl;
    std::cout << "D: " << std::is_same<int, D>::value << std::endl;
    std::cout << "E: " << std::is_same<int, E>::value << std::endl;
    std::cout << "F: " << std::is_same<int, F>::value << std::endl;

    return 0;
}