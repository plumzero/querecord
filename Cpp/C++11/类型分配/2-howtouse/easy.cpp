
#include <iostream>
#include <type_traits>
#include <string>

template<typename T>
class Storage
{
    typename std::aligned_storage<sizeof(T), alignof(T)>::type object;
public:
    Storage() {}
    ~Storage() {
        reinterpret_cast<T*>(&object)->~T();
    }
    template<typename... Args>
    void construct(Args&&... args) {
        new (&object) T(std::forward<Args>(args)...);
    }
    T& value() {
        return *reinterpret_cast<T*>(&object);
    }
};

class Apple
{
public:
    Apple(int i, std::string c) : index(i), color(c) { std::cout << "called construction" << std::endl; }
    ~Apple(){ std::cout << "called destruction" << std::endl; }
public:
    int index;
    std::string color;
};
 
int main()
{
    Storage<Apple> storeApple;
    storeApple.construct(1, "red");
    
    storeApple.value().color = "Green";
    
    std::cout << "index=" << storeApple.value().index << std::endl; 
    std::cout << "color=" << storeApple.value().color << std::endl; 
    
    return 0;
}