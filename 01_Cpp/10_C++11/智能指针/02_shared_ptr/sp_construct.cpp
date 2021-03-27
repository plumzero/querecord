
#include <iostream>
#include <memory>

/** valgrind 测试结果: 无内存泄漏 */

void pass_sp_with_value(std::shared_ptr<int> sp)
{
    std::cout << "value.use_count=" << sp.use_count() << std::endl;
}

void pass_sp_with_ref(std::shared_ptr<int>& sp)
{
    std::cout << "ref.use_count=" << sp.use_count() << std::endl;
}

int main ()
{
    {
        std::shared_ptr<int> sp1;                    /** 缺省构造 */
        std::shared_ptr<int> sp2 (new int);          /** 缺省构造 */
    }
    
    {
        std::shared_ptr<int> sp1, sp2;
        std::shared_ptr<int> sp3 = std::move(sp1);    /** 移动构造 */
        std::shared_ptr<int> sp4;
        sp4 = std::move(sp2);                         /** 移动拷贝构造 */
    }
    
    {
        std::shared_ptr<int> sp1;
        std::shared_ptr<int> sp2 = sp1;               /** 支持拷贝构造 */
        std::shared_ptr<int> sp3;
        sp3 = sp2;                                    /** 支持赋值拷贝构造*/
        std::cout << "sp1.use_count=" << sp1.use_count() << std::endl;
        std::cout << "sp2.use_count=" << sp2.use_count() << std::endl;
        std::cout << "sp3.use_count=" << sp3.use_count() << std::endl;
    }
    
    {
        std::shared_ptr<int> sp1 (new int);
        std::shared_ptr<int> sp2 = sp1;               /** 支持拷贝构造 */
        std::shared_ptr<int> sp3;
        sp3 = sp2;                                    /** 支持赋值拷贝构造*/
        std::cout << "sp1.use_count=" << sp1.use_count() << std::endl;
        std::cout << "sp2.use_count=" << sp2.use_count() << std::endl;
        std::cout << "sp3.use_count=" << sp3.use_count() << std::endl;
    }
    
    {
        int *p1 = new int;
        std::shared_ptr<int> sp1(p1);
        // int *p2 = new int;
        // std::shared_ptr<int> sp2 = p2;            /** 不支持指针直接赋值 */
    }
    
    {
        std::shared_ptr<int> sp1 (new int);
        pass_sp_with_value(sp1);
        
        std::shared_ptr<int> sp2 (new int);
        pass_sp_with_ref(sp2);
    }
    
    return 0;
}