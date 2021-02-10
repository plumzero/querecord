
#include <iostream>
#include <string>
#include <bitset>

int main()
{
    {
        /** [1] 构造函数 */
        std::cout << "构造函数测试:" << std::endl;
        std::bitset<16> foo;
        std::bitset<16> bar(0xfa2);
        std::bitset<16> baz(std::string("0101111001"));
        
        std::cout << "foo: " << foo << std::endl;
        std::cout << "bar: " << bar << std::endl;
        std::cout << "baz: " << baz << std::endl;
    }
    {
        /** [2] 引用元素 */
        std::cout << "引用元素测试:" << std::endl;
        std::bitset<4> foo;
        foo[1] = 1;             /** 0010 */
        foo[2] = foo[1];        /** 0110 */
        
        std::cout << "foo: " << foo << std::endl;
    }
    {
        /** [3] 成员函数 */
        std::cout << "成员函数测试:" << std::endl;
        std::bitset<8> foo(std::string("10110011"));
        
        std::cout << foo.count() << std::endl;
        std::cout << foo.size() << std::endl;
        size_t i;
        for (i = 0; i < foo.size(); i++) {
            std::cout << std::boolalpha << foo.test(i) << " ";
        }
        std::cout << std::endl;
    }
    {
        /** [4] any none all 成员函数 */
        std::cout << "any none all 成员函数测试:" << std::endl;
        std::bitset<8> foo(std::string("00000010"));
        std::cout << "foo: " << foo << std::endl;
        std::cout << std::boolalpha << foo.any() << std::endl;
        std::cout << std::boolalpha << foo.none() << std::endl;
        
        foo[1] = 0;
        std::cout << "foo: " << foo << std::endl;
        std::cout << std::boolalpha << foo.any() << std::endl;
        std::cout << std::boolalpha << foo.none() << std::endl;
        
        std::cout << std::boolalpha
                  << std::bitset<4>(std::string("1111")).all()
                  << std::endl;
    }
    {
        /** [5] 转换 */
        std::cout << "转换测试:" << std::endl;
        std::bitset<4>  foo(0xe);
        
        std::string bits = foo.to_string();
        std::cout << bits << std::endl;
        
        foo.set();
        std::cout << foo.to_ulong() << std::endl;
    }
    
    return 0;
}