
#include <stdint.h>
#include <iostream>
#include <string>
#include <type_traits>

typedef enum {
    VERSION_A,
    VERSION_B,
    VERSION_C,
} TAG;

using A_type = std::integral_constant<TAG, VERSION_A>;
using B_type = std::integral_constant<TAG, VERSION_B>;
using C_type = std::integral_constant<TAG, VERSION_C>;

struct Version
{
    virtual void print() = 0;
};

struct VersionA : A_type {
    int i;
    virtual void print() { std::cout << "version A" << std::endl; }
};

struct VersionB : B_type  {
    double d;
    virtual void print() { std::cout << "version B" << std::endl; }
};

struct VersionC : C_type {
    std::string s;
    virtual void print() { std::cout << "version B" << std::endl; }
};


template <typename T>
void parse_version(const T& t)
{
    return parse_version(t, std::is_base_of<A_type, T>(),
                            std::is_base_of<B_type, T>(),
                            std::is_base_of<C_type, T>());
}

template <typename T>
void parse_version(const T& t, const std::true_type&, const std::false_type&, const std::false_type&)
{
    std::cout << "A type" << std::endl;
    static_cast<VersionA>(t).print();
}

template <typename T>
void parse_version(const T& t, const std::false_type&, const std::true_type&, const std::false_type&)
{
    std::cout << "B type" << std::endl;
    static_cast<VersionB>(t).print();
}

template <typename T>
void parse_version(const T& t, const std::false_type&, const std::false_type&, const std::true_type&)
{
    std::cout << "C type" << std::endl;
    static_cast<VersionC>(t).print();
}

int main()
{   
    VersionA va;
    parse_version(va);
    
    VersionB vb;
    parse_version(vb);

    return 0;
}