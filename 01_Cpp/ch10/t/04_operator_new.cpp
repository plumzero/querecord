
#include <iostream>
#include <string.h>

class A
{
public:
    A() { std::cout << "call constructor" << std::endl; x = 100; y = 200;  }
    ~A() { std::cout << "call deconstructor" << std::endl; }

    void* operator new(size_t size) noexcept {
        void* p = malloc(size);
        std::cout << "call A::new(" << size << ") " << p << std::endl;
        return p;
    }

    void operator delete(void* p) {
        std::cout << "call A::delete " << p << std::endl;
        if (p) free(p);
    }

    void* operator new[](size_t size) noexcept {
        void* p = malloc(size);
        std::cout << "call A::new[](" << size << ") " << p << std::endl;
        return p;
    }

    void operator delete[](void* p) {
        std::cout << "call A::delete[] " << p << std::endl;
        if (p) free(p);
    }

    int x, y;
};

int main()
{
    // 单个对象
    std::cout << "one object" << std::endl;
    A* a = new A();
    delete a;

    // 数组
    std::cout << "object array" << std::endl;
    A* arr = new A[2];      // A 对象的尺寸为 8, 分配两个对象，应该是 16，但实际上是 24，奇怪...

    std::cout << arr << std::endl;
    std::cout << &arr[0] << ": arr[0].x = " << arr[0].x << ", arr[0].y = " << arr[0].y << std::endl;
    std::cout << &arr[1] << ": arr[1].x = " << arr[1].x << ", arr[1].y = " << arr[1].y << std::endl;

    delete[] arr;

    return 0;
}