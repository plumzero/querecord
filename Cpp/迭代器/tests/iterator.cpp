
#include <iostream>
#include <iterator>
#include <typeinfo>

/** 数组的迭代器应该定义为随机访问迭代器，所以应该实现随机访问迭代器相关特性 */
template <typename T>
class ArrayIterator : public std::iterator<std::random_access_iterator_tag, T>
{
public:
    using value_type               = T;
    using reference                = T&;
    using const_reference          = const T&;
    using pointer                  = T*;
    using const_pointer            = const T*;
    using iterator                 = ArrayIterator;
    using iterator_reference       = iterator&;
    using const_iterator           = const ArrayIterator;
    using const_iterator_reference = const_iterator&;
    using difference_type          = signed int;
    using size_type                = unsigned int;
    /** 构造函数 */
    ArrayIterator(value_type* p) : p(p) {}
    /** 迭代器只是指向了对象，并不对这块对象占有的资源负责，所以是浅拷贝 */
    ArrayIterator(const_iterator& ai) : p(ai.p) {}
    /** 析构函数 */
    ~ArrayIterator(){}
    /** 读写 */
    reference operator*() { return *p; }
    /** 访问 */
    pointer operator->() { if (!p) throw; return p; }
    reference operator[](size_type i) { return p[i]; }
    /** 迭代 */
    iterator_reference operator++() { ++p; return *this; }
    const_iterator operator++(int) { iterator tmp(*this); operator++(); return tmp; }
    iterator_reference operator--() { --p; return *this; }
    const_iterator operator--(int) { iterator tmp(*this); operator--(); return tmp; }
    iterator_reference operator+(difference_type o) { p += o; return *this; }
    iterator_reference operator-(difference_type o) { p -= o; return *this; }
    iterator_reference operator+=(difference_type o) { p = operator+(o); return *p; }
    iterator_reference operator-=(difference_type o) { p = operator-(o); return *p; }
    /** 比较(粗糙的实现) */
    bool operator==(const_iterator_reference rhs) { return p == rhs.p; }
    bool operator!=(const_iterator_reference rhs) { return p != rhs.p; }
    bool operator<(const_iterator_reference rhs) { return p - rhs.p < 0; }
    bool operator>(const_iterator_reference rhs) { return p - rhs.p > 0; }
    bool operator<=(const_iterator_reference rhs) { return p - rhs.p <= 0; }
    bool operator>=(const_iterator_reference rhs) { return p - rhs.p >= 0; }
private:    
    value_type* p;
};

class Stu
{
public:
    Stu(int i) : index(i) {}
    ~Stu(){}
    
    int index;
};

int main()
{
    {
        /** [1] 迭代器类型 */
        std::cout << "迭代器类型测试:" << std::endl;
        std::iterator_traits<ArrayIterator<Stu>>::iterator_category ai_ic;
        if (typeid(ai_ic) == typeid(std::random_access_iterator_tag)) {
            std::cout << "ArrayIterator's iterator is random access iterator" << std::endl;
        } else {
            std::cout << "ArrayIterator's iterator is not random access iterator" << std::endl;
        }
    }
    
    {
        /** [2] 测试 - 访问，读写，自操作迭代 */
        std::cout << "访问及读写操作:" << std::endl;
        Stu Students[] = { Stu(1), Stu(2), Stu(3), Stu(4), Stu(5) };
        ArrayIterator<Stu> begin(Students);
        ArrayIterator<Stu> end(Students + 5);
        
        for (ArrayIterator<Stu> it = begin; it != end; it++) {
            std::cout << (*it).index << " ";
            (*it).index = it->index * 2;
        }
        std::cout << std::endl;
        
        for (ArrayIterator<Stu> it = begin; it != end; ++it) {
            std::cout << it->index << " ";
        }
        std::cout << std::endl;
        
        for (ArrayIterator<Stu> it = end - 1; it > begin; --it) {
            std::cout << it->index << " ";
        }
        std::cout << std::endl;
        
        ArrayIterator<Stu> it = begin + 3;
        std::cout << it->index << std::endl;

    }
    
    return 0;
}