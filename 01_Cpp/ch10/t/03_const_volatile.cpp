
#include <stdio.h>
#include <stddef.h>

const volatile int _g = 11;
int *ptr = static_cast<int*>(const_cast<int*>(&_g));

struct TestStruct
{
    volatile const int x = 100;
    const volatile double y = 3.14;

    const int m = 1000;     // 不过实际测试下来，不用 volatile 修饰的 const 也可以通过地址进行修改
    const double n = 2.71;
};

int main()
{
    // 全局变量测试
    // _g = 100;    // compile failed
    *ptr = 100;
    printf("_g=%d\n", _g);


    // 结构体测试
    struct TestStruct val;

    printf ("offsetof(struct TestStruct, x) is %d\n",(int)offsetof(struct TestStruct, x));
    printf ("offsetof(struct TestStruct, y) is %d\n",(int)offsetof(struct TestStruct, y));
    printf ("offsetof(struct TestStruct, m) is %d\n",(int)offsetof(struct TestStruct, m));
    printf ("offsetof(struct TestStruct, n) is %d\n",(int)offsetof(struct TestStruct, n));

    printf("val.x = %d, val.y = %lf, val.m = %d, val.n = %lf\n", 
                                    *((int*)((char*)&val + offsetof(struct TestStruct, x))), 
                                    *((double*)((char*)&val + offsetof(struct TestStruct, y))), 
                                    *((int*)((char*)&val + offsetof(struct TestStruct, m))),    // 这样就没问题了
                                    *((double*)((char*)&val + offsetof(struct TestStruct, n)))); 

    // val.x = 100;
    // val.y = 3.14;
    // 像上面这样赋值是编译不过去的
    // 可以像下面这样
    *(int*)((char*)&val + offsetof(struct TestStruct, x)) = 99;
    *(double*)((char*)&val + offsetof(struct TestStruct, y)) = 99.9991;
    *(int*)((char*)&val + offsetof(struct TestStruct, m)) = 999;
    *(double*)((char*)&val + offsetof(struct TestStruct, n)) = 777.223;
    printf("val.x = %d, val.y = %lf, val.m = %d, val.n = %lf\n", val.x, val.y, val.m, val.n);
    

    return 0;
}