
#include <iostream>
#include <type_traits>

class A {};

class B : A {};

class C {};

int main() {
    std::cout << std::boolalpha;
    std::cout << "a2b:  " << std::is_base_of<A, B>::value << std::endl;
    std::cout << "b2a:  " << std::is_base_of<B, A>::value << std::endl;
    std::cout << "c2b:  " << std::is_base_of<C, B>::value << std::endl;
    std::cout << "same type:  " << std::is_base_of<C, C>::value << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    std::cout << "A, const B:  " << std::is_base_of<A, const B>::value << std::endl;
    std::cout << "A&, B&:  " << std::is_base_of<A&, B&>::value << std::endl;
    
    std::cout << "int, int:  " << std::is_base_of<int, int>::value << std::endl;
    
    return 0;
}