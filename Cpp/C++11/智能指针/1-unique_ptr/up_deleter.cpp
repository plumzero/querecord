
#include <iostream>
#include <memory>

class Stu
{
public:
    Stu(int i) : index(i) {}
    int index;
};

template<typename T>
class stu_deleter
{
public:
    int count;
    stu_deleter() : count(0) {}
    void operator()(T* ptr) {
        std::cout << "释放 Stu: index=" << ptr->index << "[count=" << ++count << "]" << std::endl;
        delete ptr;
    }
};

/**
 * 本示例是对左值删除器的示例，如果想右值删除器示例，那就像这样吧
 *  std::unique_ptr<Stu, stu_deleter<Stu>> stu1(new Stu(1), std::move(stu_deleter<Stu>()));
 */

int main()
{
    {
        /** [1] 朴素的写法一 */
        std::cout << "[1] 朴素的写法: 构造形式" << std::endl;
        std::unique_ptr<Stu, stu_deleter<Stu>> stu1(new Stu(1), stu_deleter<Stu>());
        std::unique_ptr<Stu, stu_deleter<Stu>> stu2(new Stu(2), stu_deleter<Stu>());
        std::unique_ptr<Stu, stu_deleter<Stu>> stu3(new Stu(3), stu_deleter<Stu>());
        std::unique_ptr<Stu, stu_deleter<Stu>> stu4(new Stu(4), stu_deleter<Stu>());
    }
    {
        /** [2] 朴素的写法二 */
        std::cout << "[2] 朴素的写法: 拷贝形式" << std::endl;
        stu_deleter<Stu> my_deleter;
        std::unique_ptr<Stu, stu_deleter<Stu>> stu1(new Stu(1), my_deleter);
        std::unique_ptr<Stu, stu_deleter<Stu>> stu2(new Stu(2), my_deleter);
        std::unique_ptr<Stu, stu_deleter<Stu>> stu3(new Stu(3), my_deleter);
        std::unique_ptr<Stu, stu_deleter<Stu>> stu4(new Stu(4), my_deleter);
    }
    {
        // 可以看出，删除器是通过对象进行构造的。如果一个删除器一个构造(或拷贝)，效率肯定低，所以使用引用吧。
        /** [3] 引用写法 */
        std::cout << "[3] 高效的写法: 引用形式" << std::endl;
        stu_deleter<Stu> my_deleter;
        std::unique_ptr<Stu, stu_deleter<Stu>&> stu1(new Stu(1), my_deleter);
        std::unique_ptr<Stu, stu_deleter<Stu>&> stu2(new Stu(2), my_deleter);
        std::unique_ptr<Stu, stu_deleter<Stu>&> stu3(new Stu(3), my_deleter);
        std::unique_ptr<Stu, stu_deleter<Stu>&> stu4(new Stu(4), my_deleter);
    }
    
    return 0;
}