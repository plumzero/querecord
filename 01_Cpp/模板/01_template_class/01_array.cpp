
#include <cstdlib>
#include <stdexcept>
#include <iostream>

template <typename T>
class Array
{
private:
    T * elements;
    size_t count;
public:
    explicit Array(size_t arraySize);
    Array(const Array & other);
    Array(Array && other);
    virtual ~Array();
    T& operator[](size_t index);
    const T& operator()(size_t index) const;
    
    Array& operator=(const Array & rhs);
    Array& operator=(Array && rhs);
    size_t size() { return count; }
};

template <typename T>
inline Array<T>::Array(size_t arraySize)
try : elements { new T[arraySize] }, count{arraySize} {}
catch(const std::exception& e)
{
    std::cerr << "Memory allocation failure in Array constructor." << std::endl;
}

template <typename T>
inline Array<T>::~Array() {}

int main()
{
    Array<int> data{40};
    
    return 0;
}