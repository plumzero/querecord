
#include <iostream>
#include <memory>

int main ()
{
    {
        std::unique_ptr<int> u1;                    /** 缺省构造 */
        std::unique_ptr<int> u2 (new int);          /** 缺省构造 */
    }
    
    {
        std::unique_ptr<int> u1, u2;
        std::unique_ptr<int> u3 = std::move(u1);    /** 移动构造 */
        std::unique_ptr<int> u4;
        u4 = std::move(u2);                         /** 移动拷贝构造 */
    }
    
    {
        std::unique_ptr<int> u1, u2;
        // std::unique_ptr<int> u3 = u1;            /** 不支持拷贝构造 */
        std::unique_ptr<int> u4;
        // u4 = u2;                                 /** 也不支持赋值拷贝构造*/
    }
    
    return 0;
}