
#include <iostream>
#include <string.h>

class A
{
public:
    A() { x = 1; y = 2; }
    ~A() {}

    void* operator new(size_t size) {
        std::cout << "call A::new" << std::endl;
        return malloc(size);
    }

    void operator delete(void* p) {
        std::cout << "call A::delete " << p << std::endl;
        if (p) {
            free(p);
        }
    }

    int x, y;
};

int main()
{
    A* a = new A();

    std::cout << "allocate address: " << a << std::endl;

    std::cout << "a->x = " << a->x << ", a->y = " << a->y << std::endl;

    delete a;

    return 0;
}