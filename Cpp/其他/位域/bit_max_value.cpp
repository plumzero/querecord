
#include <stdio.h>

typedef struct _bit_struct {
    unsigned int a:3;
    unsigned int b:5;
    unsigned int c:7;
} BitStruct;

int main()
{
    {
        BitStruct bs = { .a = 7, .b = 31, .c = 127 };
        
        printf("a=%d,b=%d,c=%d\n", bs.a, bs.b, bs.c);   // a=7,b=31,c=127
    }

    {
        BitStruct bs = { .a = 8, .b = 32, .c = 128 };
        
        printf("a=%d,b=%d,c=%d\n", bs.a, bs.b, bs.c);   // a=0,b=0,c=0
    }
    
    {
        BitStruct bs = { .a = 9, .b = 33, .c = 129 };
        
        printf("a=%d,b=%d,c=%d\n", bs.a, bs.b, bs.c);   // a=1,b=1,c=1
    }
    
    return 0;
}



