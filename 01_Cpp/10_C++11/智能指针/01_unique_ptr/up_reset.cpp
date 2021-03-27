
#include <iostream>
#include <memory>

int main()
{
    std::unique_ptr<int> u1;

    u1.reset (new int);             /** 接管 */
    *u1 = 5;
    std::cout << *u1 << std::endl;

    u1.reset (new int);             /** 销毁原来的对象，接管新对象 */
    std::cout << *u1 << std::endl;

    *u1 = 10;
    std::cout << *u1 << std::endl;

    u1.reset();                     /** 销毁对象 */
    
    return 0;
}
