
#include <iostream>
#include <memory>

int main ()
{
    {
        struct A;
        struct B;
        
        struct A {
            std::shared_ptr<B> bptr;
            ~A() { std::cout << "A is deleted!" << std::endl; }
        };
        
        struct B {
            std::shared_ptr<A> aptr;
            ~B() { std::cout << "B is deleted!" << std::endl; }
        };
        
        std::shared_ptr<A> ap(new A);
        std::shared_ptr<B> bp(new B);
        ap->bptr = bp;
        bp->aptr = ap;
    }
    
    {
        struct A;
        struct B;
        
        struct A {
            std::shared_ptr<B> bptr;
            ~A() { std::cout << "A is deleted!" << std::endl; }
        };
        
        struct B {
            std::weak_ptr<A> aptr;
            ~B() { std::cout << "B is deleted!" << std::endl; }
        };
        
        std::shared_ptr<A> ap(new A);
        std::shared_ptr<B> bp(new B);
        ap->bptr = bp;
        bp->aptr = ap;
    }

    return 0;
}