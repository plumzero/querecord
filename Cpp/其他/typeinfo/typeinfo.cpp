
#include <iostream>
#include <typeinfo>

class Base
{};
class Derived : public Base
{};

class VBase
{
public:
    virtual ~VBase() {}
};
class VDerived : public VBase
{
public:
    virtual ~VDerived() {}
};

int main()
{
    {
        /** [1] 编译时计算 - 内建类型 */
        std::cout << "内建类型 - 编译时计算:" << std::endl;
        std::cout << "int:           " << typeid(int).name() << std::endl;
        std::cout << "unsigned:      " << typeid(unsigned).name() << std::endl;
        std::cout << "long:          " << typeid(long).name() << std::endl;
        std::cout << "unsigned long: " << typeid(unsigned long).name() << std::endl;
        std::cout << "char:          " << typeid(char).name() << std::endl;
        std::cout << "unsigned char: " << typeid(unsigned char).name() << std::endl;
        std::cout << "float:         " << typeid(float).name() << std::endl;
        std::cout << "double:        " << typeid(double).name() << std::endl;
        std::cout << "std::string:   " << typeid(std::string).name() << std::endl;
        std::cout << "std::type_info:" << typeid(std::type_info).name() << std::endl;
    }
    {
        /** [2] 编译时计算 - 自定义类型 */
        Base b;
        Derived d;
        Base *pbb = &b;
        Base *pbd = &d;
        
        std::cout << "自定义类型 - 编译时计算:" << std::endl;
        std::cout << "Base:          " << typeid(Base).name() << std::endl;
        std::cout << "Derived:       " << typeid(Derived).name() << std::endl;
        std::cout << "b:             " << typeid(b).name() << std::endl;
        std::cout << "d:             " << typeid(d).name() << std::endl;
        std::cout << "pbb:           " << typeid(pbb).name() << std::endl;
        std::cout << "pbd:           " << typeid(pbd).name() << std::endl;
        std::cout << "*pbb:          " << typeid(*pbb).name() << std::endl;
        std::cout << "*pbd:          " << typeid(*pbd).name() << std::endl; /** 静态截断 */
    }
    {
        /** [3] 运行时计算 - 自定义类型 */
        VBase b;
        VDerived d;
        VBase *pbb = &b;
        VBase *pbd = &d;
        
        std::cout << "自定义类型 - 运行时计算:" << std::endl;
        std::cout << "VBase:         " << typeid(VBase).name() << std::endl;
        std::cout << "VDerived:      " << typeid(VDerived).name() << std::endl;
        std::cout << "b:             " << typeid(b).name() << std::endl;
        std::cout << "d:             " << typeid(d).name() << std::endl;
        std::cout << "pbb:           " << typeid(pbb).name() << std::endl;
        std::cout << "pbd:           " << typeid(pbd).name() << std::endl;
        std::cout << "*pbb:          " << typeid(*pbb).name() << std::endl;
        std::cout << "*pbd:          " << typeid(*pbd).name() << std::endl; /** 动态获取 */
    }
    {
        /** [4] std::bad_cast 示例 */
        std::cout << "std::bad_cast 示例" << std::endl;
        try {
            VBase b;
            Derived& rd = dynamic_cast<Derived&>(b);
        }
        catch (std::bad_cast& bc) {
            std::cerr << "bad_cast caught: " << bc.what() << std::endl;
        }
    }
    
    {
        /** [5] std::bad_typeid 示例 */
        std::cout << "std:;bad_typeid 示例" << std::endl;
        try {
            VBase* pb = nullptr;
            std::cout << typeid(*pb).name();
        }
        catch (std::bad_typeid& bt) {
            std::cerr << "bad_typeid caught: " << bt.what() << std::endl;
        }
    }
    
    return 0;
}