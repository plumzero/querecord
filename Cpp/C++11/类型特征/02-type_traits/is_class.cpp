
// is_class example
#include <iostream>
#include <type_traits>
#include <string>
#include <vector>
#include <list>
#include <map>

struct A {};
class B {};
union C {int i; float f;};
enum class D {x,y,z};

std::string str;

std::vector<int> vec;
std::list<double> lst;
std::map<int, const char *> mic;

int main()
{
    std::cout << std::boolalpha;
    std::cout << "is_class:" << std::endl;
    std::cout << "struct A: " << std::is_class<A>::value << std::endl;
    std::cout << "class B: " << std::is_class<B>::value << std::endl;
    std::cout << "union C: " << std::is_class<C>::value << std::endl;
    std::cout << "enum class D: " << std::is_class<D>::value << std::endl;
    
    std::cout << "======================================" << std::endl;
    std::cout << "bool: " << std::is_class<bool>::value << std::endl;
    std::cout << "char: " << std::is_class<char>::value << std::endl;
    std::cout << "signed char: " << std::is_class<signed char>::value << std::endl;
    std::cout << "unsigned char: " << std::is_class<unsigned char>::value << std::endl;
    std::cout << "short: " << std::is_class<short>::value << std::endl;
    std::cout << "int: " << std::is_class<int>::value << std::endl;
    std::cout << "long: " << std::is_class<long>::value << std::endl;
    std::cout << "double: " << std::is_class<double>::value << std::endl;
    
    std::cout << "======================================" << std::endl;
    std::cout << "char*: " << std::is_class<char*>::value << std::endl;
    std::cout << "signed char*: " << std::is_class<signed char*>::value << std::endl;
    std::cout << "unsigned char*: " << std::is_class<unsigned char*>::value << std::endl;
    std::cout << "short*: " << std::is_class<short*>::value << std::endl;
    std::cout << "int*: " << std::is_class<int*>::value << std::endl;
    std::cout << "long*: " << std::is_class<long*>::value << std::endl;
    std::cout << "double*: " << std::is_class<double*>::value << std::endl; 
    
    std::cout << "======================================" << std::endl;
    std::cout << "std::string: " << std::is_class<std::string>::value << std::endl;
    std::cout << "std::string*: " << std::is_class<std::string*>::value << std::endl;
    
    std::cout << "======================================" << std::endl;
    std::cout << "std::vector<int>: " << std::is_class<std::vector<int>>::value << std::endl;
    std::cout << "std::list<double>: " << std::is_class<std::list<double>>::value << std::endl;
    std::cout << "std::map<int, const char*>: " << std::is_class<std::map<int, const char*>>::value << std::endl;
    std::cout << "std::pair <std::string,double>: " << std::is_class<std::pair <std::string,double>>::value << std::endl;
    
    return 0;
}