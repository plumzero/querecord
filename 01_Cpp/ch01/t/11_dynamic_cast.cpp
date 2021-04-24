#include <iostream>
#include <exception>
using namespace std;

class Base { virtual void dummy() {} };
class Derived: public Base { int a; };

int main ()
{
    try {
        Base * pba = new Derived;
        Base * pbb = new Base;
        Derived * pd;

        pd = dynamic_cast<Derived*>(pba);   /** 最常见应用 */
        if (pd == nullptr) std::cout << "Null pointer on first type-cast." << std::endl;

        pd = dynamic_cast<Derived*>(pbb);
        if (pd == nullptr) std::cout << "Null pointer on second type-cast." << std::endl;
    } catch (std::exception& e) { std::cout << "Exception: " << e.what();}
    
    return 0;
}