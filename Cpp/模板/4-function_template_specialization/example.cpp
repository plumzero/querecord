#include <cstdio>
#include <string>
#include <cctype>
#include <stdexcept>

namespace
{
    inline int digit_to_number(char c) throw () { return c - '0'; }
    inline char number_to_digit(int i) throw () { return i + '0'; }
};

template<typename L, typename R>
inline L absorb_digit(L value, R digit) throw ()
{
    return 10 * value + digit;
}

template<typename T> void from_string(const char Str[], T &Obj);

template<>
void from_string(const char Str[], long &Obj)
{
    int i = 0;
    long result = 0;
    
    if (! isdigit(Str[i])) {
        if (Str[i] != '-')
            throw std::runtime_error("Could not convert string to integer: '" + 
                std::string(Str) + "'");
        
        for (++i; isdigit(Str[i]); ++i) {
            const long newresult = absorb_digit(result, -digit_to_number(Str[i]));
            if (newresult > result)
                throw std::runtime_error("Integer too small to read: " + std::string(Str));
            result = newresult;
        }
    } else for (; isdigit(Str[i]); ++i) {
        const long newresult = absorb_digit(result, digit_to_number(Str[i]));
        if (newresult < result)
            throw std::runtime_error("Integer too large to read: " + std::string(Str));
        result = newresult;
    }
    
    if (Str[i])
        throw std::runtime_error("Unexpected text after integer: '" + std::string(Str) + "'");
    
    Obj = result;
}

template<>
void from_string(const char Str[], unsigned long &Obj)
{
    int i = 0;
    unsigned long result;
    
    if (! Str) throw std::runtime_error("Attempt to convert NULL string to integer");
    
    if (! isdigit(Str[i]))
        throw std::runtime_error("Could not convert string to unsigned integer: '" +
            std::string(Str) + "'");
    
    for (result = 0; isdigit(Str[i]); ++i) {
        const unsigned long newres = absorb_digit(result, digit_to_number(Str[i]));
        if (newres < result)
            throw std::runtime_error("Unsigned text too large to read: " + std::string(Str));
        
        result = newres;
    }
    
    if (Str[i])
        throw std::runtime_error("Unexpected text after integer: '" + std::string(Str) + "'");
    
    Obj = result;
}

int main()
{
    long l = 0;
    from_string("-1345", l);
    printf("long = %ld\n", l);
    
    unsigned long ul = 0;
    from_string("12345", ul);
    printf("unsigned long = %lu\n", ul);
    
    
    return 0;
}