
#include <iostream>
#include <memory>

class Stu
{
public:
    Stu(int i) : index(i) {}
    int index;
};

class stu_deleter
{
public:
    stu_deleter() {}
    void operator()(Stu* ptr) {
        std::cout << "释放 Stu: index=" << ptr->index << std::endl;
        delete ptr;
    }
};

int main()
{
    {
        /** [1] 构造形式 */
        std::cout << "[1] 构造形式" << std::endl;
        std::shared_ptr<Stu> stu1(new Stu(1), stu_deleter());
        std::shared_ptr<Stu> stu2 = stu1;
        std::shared_ptr<Stu> stu3 = stu2;
        std::shared_ptr<Stu> stu4 = stu3;
    }
    {
        /** [2] 拷贝形式 */
        std::cout << "[2] 拷贝形式" << std::endl;
        stu_deleter my_deleter;
        std::shared_ptr<Stu> stu1(new Stu(1), my_deleter);
        std::shared_ptr<Stu> stu2 = stu1;
        std::shared_ptr<Stu> stu3 = stu2;
        std::shared_ptr<Stu> stu4 = stu3;
    }
    {
        /** [3] lambda 表达式 */
        std::cout << "[3] lambda 形式" << std::endl;
        std::shared_ptr<Stu> stu1(new Stu(1), [](Stu* ptr) {
            std::cout << "释放 Stu: index=" << ptr->index <<  std::endl;
            delete ptr;
        });
        std::shared_ptr<Stu> stu2 = stu1;
        std::shared_ptr<Stu> stu3 = stu2;
        std::shared_ptr<Stu> stu4 = stu3;
    }
    
    return 0;
}