
#include <iostream>
#include <iomanip>
#include <type_traits>
#include <string>

// 2019.02.19

#define NULL_FLAG               0 << 0
#define CHAR_FLAG               1 << 0
#define UCHAR_FLAG              1 << 1
#define SCHAR_FLAG              1 << 2
#define INT_FLAG                1 << 3
#define UINT_FLAG               1 << 4
#define LLONG_FLAG              1 << 5
#define ULLONG_FLAG             1 << 6
#define FLOAT_FLAG              1 << 7
#define DOUBLE_FLAG             1 << 8
#define BOOL_FLAG               1 << 9
#define STRING_FLAG             1 << 10

template<typename T>
static void type_check(T& data) {
    std::cout << "type checking ..." << std::endl;
    // char
    if (std::is_same<typename std::decay<T>::type, char>::value) {
        std::cout << "type is char" << std::endl;
    }
    if (std::is_same<typename std::decay<T>::type, unsigned char>::value) {
        std::cout << "type is unsigend char" << std::endl;
    }
    if (std::is_same<typename std::decay<T>::type, signed char>::value) {
        std::cout << "type is signed char" << std::endl;
    }
    if (std::is_same<typename std::decay<T>::type, char*>::value) {
        std::cout << "type is char*" << std::endl;
    }
    if (std::is_same<typename std::decay<T>::type, unsigned char*>::value) {
        std::cout << "type is unsigend char*" << std::endl;
    }
    if (std::is_same<typename std::decay<T>::type, signed char*>::value) {
        std::cout << "type is signed char*" << std::endl;
    }
    // short
    if (std::is_same<typename std::decay<T>::type, short>::value) {
        std::cout << "type is short" << std::endl;
    }
    if (std::is_same<typename std::decay<T>::type, unsigned short>::value) {
        std::cout << "type is unsigned short" << std::endl;
    }
    if (std::is_same<typename std::decay<T>::type, signed short>::value) {
        std::cout << "type is signed short" << std::endl;
    }
    // int
    if (std::is_same<typename std::decay<T>::type, int>::value) {
        std::cout << "type is int" << std::endl;
    }
    if (std::is_same<typename std::decay<T>::type, unsigned int>::value) {
        std::cout << "type is unsigend int" << std::endl;
    }
    if (std::is_same<typename std::decay<T>::type, signed int>::value) {
        std::cout << "type is signed int" << std::endl;
    }
    if (std::is_same<typename std::decay<T>::type, int*>::value) {
        std::cout << "type is int*" << std::endl;
    }
    if (std::is_same<typename std::decay<T>::type, unsigned int*>::value) {
        std::cout << "type is unsigend int*" << std::endl;
    }
    if (std::is_same<typename std::decay<T>::type, signed int*>::value) {
        std::cout << "type is signed int*" << std::endl;
    }
    // long
    if (std::is_same<typename std::decay<T>::type, long>::value) {
        std::cout << "type is long" << std::endl;
    }
    if (std::is_same<typename std::decay<T>::type, unsigned long>::value) {
        std::cout << "type is unsigend long" << std::endl;
    }
    if (std::is_same<typename std::decay<T>::type, signed long>::value) {
        std::cout << "type is signed long" << std::endl;
    }
    // long long
    if (std::is_same<typename std::decay<T>::type, long long>::value) {
        std::cout << "type is long long" << std::endl;
    }
    if (std::is_same<typename std::decay<T>::type, unsigned long long>::value) {
        std::cout << "type is unsigend long long" << std::endl;
    }
    if (std::is_same<typename std::decay<T>::type, signed long long>::value) {
        std::cout << "type is signed long long" << std::endl;
    }
    // float
    if (std::is_same<typename std::decay<T>::type, float>::value) {
        std::cout << "type is float" << std::endl;
    }
    // double
    if (std::is_same<typename std::decay<T>::type, double>::value) {
        std::cout << "type is double" << std::endl;
    }
    // bool
    if (std::is_same<typename std::decay<T>::type, bool>::value) {
        std::cout << "type is bool" << std::endl;
    }
    // std::string
    if (std::is_same<typename std::decay<T>::type, std::string>::value) {
        std::cout << "type is std::string" << std::endl;
    }
    
    std::cout << "checking ok." << std::endl << std::endl;
}

template<typename T>
static int check_type(T& data) {
    int flag = NULL_FLAG;
    if (std::is_same<typename std::decay<T>::type, char>::value) {
        flag = CHAR_FLAG;
    } else if (std::is_same<typename std::decay<T>::type, unsigned char>::value) {
        flag = UCHAR_FLAG;
    } else if (std::is_same<typename std::decay<T>::type, signed char>::value) {
        flag = SCHAR_FLAG;
    } else if (std::is_same<typename std::decay<T>::type, int>::value) {
        flag = INT_FLAG;
    } else if (std::is_same<typename std::decay<T>::type, unsigned int>::value) {
        flag = UINT_FLAG;
    } else if (std::is_same<typename std::decay<T>::type, long long>::value) {
        flag = LLONG_FLAG;
    } else if (std::is_same<typename std::decay<T>::type, unsigned long long>::value) {
        flag = ULLONG_FLAG;
    } else if (std::is_same<typename std::decay<T>::type, float>::value) {
        flag = FLOAT_FLAG;
    } else if (std::is_same<typename std::decay<T>::type, double>::value) {
        flag = DOUBLE_FLAG;
    } else if (std::is_same<typename std::decay<T>::type, bool>::value) {
        flag = BOOL_FLAG;
    } else if (std::is_same<typename std::decay<T>::type, std::string>::value) {
        flag = STRING_FLAG;
    }
    return flag;
}

int main() {
    // char
    char cs[] = "hello world";      // char, unsigned char, signed char 均不同
    type_check(cs);
    unsigned char ch = 'a';
    type_check(ch);
    signed char scs[] = { 80, 56, 73 };
    type_check(scs);
    // short
    short sh = 57;                  // signed short 与 short 等同
    type_check(sh);
    unsigned short ush = 63;
    type_check(ush);
    signed short ssh = -98;
    type_check(ssh);
    // int
    int is[] = {10, -20, 30};       // signed int 与 int 等同
    type_check(is);
    unsigned int i = 33;
    type_check(i);
    signed int si = -10;
    type_check(si);
    // long
    long lo = 19;                   // signed long 与 long 等同
    type_check(lo);
    unsigned long ulo = 90;
    type_check(ulo);
    signed long slo = -93;
    type_check(slo);
    // long long
    long long loo = 19;             // signed long 与 long 等同
    type_check(loo);
    unsigned long long uloo = 90;
    type_check(uloo);
    signed long long sloo = -93;
    type_check(sloo);
    // float
    float ft = 3.14;
    type_check(ft);
    // double
    double de = 2.71828;
    type_check(de);
    // bool
    bool bl = true;
    type_check(bl);
    // std::string
    std::string str("hello world");
    type_check(str);

    // check_type 模板测试
    std::cout << check_type(loo) << std::endl;
    
    
    return 0;
}