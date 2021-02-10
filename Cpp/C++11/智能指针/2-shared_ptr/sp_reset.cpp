
#include <iostream>
#include <memory>

int main ()
{
    {
        /** [1] 简单的使用方法 */
        std::shared_ptr<int> sp;

        sp.reset (new int);             /** 接管 */
        *sp = 5;
        std::cout << *sp << std::endl;

        sp.reset (new int);             /** 销毁原来的管理对象，接管新对象 */
        std::cout << *sp << std::endl;

        *sp = 10;
        std::cout << *sp << std::endl;

        sp.reset();                     /** 销毁管理对象 */
    }
    {
        /** [2] 引用计数的变化 */
        std::shared_ptr<int> sp1 (new int);
        std::shared_ptr<int> sp2 = sp1;
        std::shared_ptr<int> sp3 = sp2;
        std::cout << "sp1.use_count=" << sp1.use_count() << std::endl;
        std::cout << "sp2.use_count=" << sp2.use_count() << std::endl;
        std::cout << "sp3.use_count=" << sp3.use_count() << std::endl;
        
        sp3.reset(new int);
        std::cout << "sp1.use_count=" << sp1.use_count() << std::endl;
        std::cout << "sp2.use_count=" << sp2.use_count() << std::endl;
        std::cout << "sp3.use_count=" << sp3.use_count() << std::endl;
    }

    return 0;
}