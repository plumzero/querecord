
#include <iostream>

void func(void)
{
    std::cout << __FUNCTION__ << " : " << __LINE__ << std::endl;
}
struct Foo
{
    void operator()(void)
    {
        std::cout << __FUNCTION__ << " : " << __LINE__ << std::endl;
    }
};
struct Bar
{
    using fr_t = void(*)(void);
    static void func(void)
    {
        std::cout << __FUNCTION__ << " : " << __LINE__ << std::endl;
    }
    operator fr_t(void)
    {
        return func;
    }
};
struct A
{
    int a_;
    
    void mem_func(void)
    {
        std::cout << __FUNCTION__ << " : " << __LINE__ << std::endl;
    }
};

int main()
{
    void (* func_ptr)(void) = &func;                // 1. 函数指针
    func_ptr();
    
    Foo foo;                                        // 2. 仿函数
    foo();
    
    Bar bar;                                        // 3. 可被转换为函数指针的类对象
    bar();
    
    void (A::*mem_func_ptr)(void) = &A::mem_func;   // 4. 类成员函数指针
    int A::*mem_obj_ptr = &A::a_;                   //    或者是类成员指针
    
    A aa;
    (aa.*mem_func_ptr)();
    aa.*mem_obj_ptr = 123;
    
    return 0;
}