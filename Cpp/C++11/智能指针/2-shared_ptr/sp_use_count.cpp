
#include <iostream>
#include <memory>

/** 复制智能指针指向同一份资源，引用计数加 1 */
void test1(std::shared_ptr<int> ptr)
{
    std::cout << "copy: " << ptr.use_count() << std::endl;
}

/** 获得指向资源的智能指针的引用，引用计数不变 */
void test2(std::shared_ptr<int> & ptr)
{
    std::cout << "refer: " << ptr.use_count() << std::endl;
}

/** 复制智能指针指向同一份资源，引用计数加 1 */
void test3(void * arg)
{
    std::shared_ptr<int> ptr = *(std::shared_ptr<int>*)arg;
    std::cout << "shared ptr: " << ptr.use_count() << std::endl;
}

/** 裸指针，引用计数不变 */
void test4(void * arg)
{
    int * p = (int*)arg;
    std::cout << *p << std::endl;
}

int main()
{
    std::shared_ptr<int> p = std::make_shared<int>(10);
    
    std::cout << __LINE__ << " " << p.use_count() << std::endl;
    
    test1(p);
    std::cout << __LINE__ << " " << p.use_count() << std::endl;
    
    test2(p);
    std::cout << __LINE__ << " " << p.use_count() << std::endl;
    
    test3(&p);
    std::cout << __LINE__ << " " << p.use_count() << std::endl;
    
    test4(p.get());
    std::cout << __LINE__ << " " << p.use_count() << std::endl;
    
    return 0;
}