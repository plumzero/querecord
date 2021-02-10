
#include <iostream>
#include <utility>

class ConstructTest
{
public:
    /** 缺省构造 */
    ConstructTest(){  std::cout << "default construct" << std::endl; }
    /** 析构 */
    ~ConstructTest(){ std::cout << "destruct" << std::endl; }
    /** 拷贝构造 */
    ConstructTest(const ConstructTest& ct) { std::cout << "copy construct" << std::endl; }
    /** 赋值拷贝构造 */
    ConstructTest& operator= (const ConstructTest& ct) { std::cout << "assign copy construct" << std::endl; }
    /** 移动构造 */
    ConstructTest(const ConstructTest&& ct) { std::cout << "move construct" << std::endl; }
    /** 移动赋值构造 */
    ConstructTest&& operator= (const ConstructTest&& ct) { std::cout << "move copy construct" << std::endl; }
};

ConstructTest return_temp()
{
    return ConstructTest();
}

ConstructTest&& return_rref()
{
    return std::move(ConstructTest());
}

int main()
{
    /** [1] 缺省构造示例 */
    {
        std::cout << "缺省构造示例:" << std::endl;
        ConstructTest ct;
        ConstructTest ct1 = return_temp();  /** 虽然返回的是一个右值，但调用的却是缺省，并不是预
                                                期的移动构造。大概是编译器开启了函数返回值优化。 */
        ConstructTest ct2(return_temp());
    }
    /** [2] 拷贝构造示例 */
    {
        std::cout << "拷贝构造示例:" << std::endl;
        ConstructTest ct;
        ConstructTest ct1(ct);
        ConstructTest ct2 = ct;
    }
    /** [3] 赋值拷贝构造示例 */
    {
        std::cout << "赋值拷贝构造示例:" << std::endl;
        ConstructTest ct;
        ConstructTest ct1;
        ct1 = ct;
    }
    /** [4] 移动构造示例 */
    {
        std::cout << "移动构造示例:" << std::endl;
        ConstructTest ct1, ct2;
        ConstructTest _ct1(std::move(ct1));
        ConstructTest _ct2 = std::move(ct2);
        ConstructTest _ct3 = std::move(return_temp());
        ConstructTest _ct4 = return_rref();
        ConstructTest _ct5(return_rref());
    }
    /** [5] 移动赋值构造示例 */
    {
        std::cout << "移动赋值构造示例:" << std::endl;
        ConstructTest ct1;
        ConstructTest _ct1, _ct2;
        _ct1 = std::move(ct1);
        _ct2 = return_temp();       /** 是移动赋值构造了 */
        
        ConstructTest _ct3;
        _ct3 = ConstructTest();
        
        ConstructTest _ct4(ConstructTest());
    }
    
    return 0;
}