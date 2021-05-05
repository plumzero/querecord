
#include <stdio.h>
typedef int DataType;
#include "SeqStack.h"

void Conversion2Oct(int N)
{
    SeqStack S;
    int x;
    
    InitStack(&S);
    
    while (N > 0) {
        x = N % 8;
        PushStack(&S, x);
        N /= 8;
    }
    
    while (! StackEmpty(S)) {
        PopStack(&S, &x);
        printf("%d", x);
    }
    printf("\n");
}

void Conversion(int N)
{
    int stack[100], top;
    top = 0;
    
    while (N > 0) {
        stack[top++] = N % 8;
        N /= 8;
    }
    
    while (top > 0) {
        top--;
        printf("%d", stack[top]);
    }
    printf("\n");
}

int main()
{
    Conversion2Oct(45);
    Conversion2Oct(111);
    Conversion2Oct(22);
    
    Conversion(45);
    Conversion(111);
    Conversion(22);
    
    return 0;
}