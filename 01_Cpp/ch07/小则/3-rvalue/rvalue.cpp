

#include <stdio.h>
#include <iostream>
#include <utility>

int g_constructCount = 0;
int g_copyConstructCount = 0;
int g_destructCount = 0;

struct A
{
    A() { std::cout << "coustruct: " << ++g_constructCount << std::endl; }
    A(const A& a) { std::cout << "copy construct: " << ++g_copyConstructCount << std::endl; }
    ~A() { std::cout << "destruct: " << ++g_destructCount << std::endl; }
};

A&& GetA() { return std::move(A()); }

int main()
{
    A&& a = GetA();
    
    printf("&a=%p\n", &a);
    return 0;
}