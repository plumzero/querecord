
#include <iostream>

template<typename T, typename U>
int bit_copy(T& a, U& b)
{
    static_assert(sizeof(a) == sizeof(b), "the parameters of bit_copy must have same width.");
}

enum FeatureSupports {
    C99         = 1 << 0,
    ExtInt      = 1 << 1,
    SAssert     = 1 << 2,
    NoExcept    = 1 << 3,
    SMAX        = 1 << 4,
};

int main()
{
    {
        int *p;
        long l;
        bit_copy(l, p);

        int i;
        double d;
        // bit_copy(d, i);  // compile failed
    }

    {
        static_assert((SMAX - 1) == (C99 | ExtInt | SAssert | NoExcept), "enum not complete");
    }

    return 0;
}