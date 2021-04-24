
#include <iostream>
#include <memory>

int main()
{
    std::unique_ptr<int> u1 (new int);
    int * p;

    *u1 = 10;
    
    p = u1.release();

    // delete p;


    bool would_free = false;
    
    if (would_free) {
        /** 直接释放 */
        delete p;
    } else {
        /** 智能指针接管 */
        std::unique_ptr<int> u2;
        u2.reset(p);
        
        std::cout << "p points to " << *u2 << std::endl;
    }
    
    return 0;
}
