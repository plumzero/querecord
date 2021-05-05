
#include <stdio.h>
#include <stdlib.h>

#define STACKSIZE 100
typedef char DataType;

#include "SSeqStack.h"

int main()
{
    SSeqStack S;
    int i;
    DataType a[] = { 'a', 'b', 'c', 'd', 'e' };
    DataType b[] = { 'x', 'y', 'z', 'r' };
    DataType e1, e2;
    
    InitStack(&S);
    
    for (i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
        if (PushStack(&S, a[i], 0) == 0) {
            printf("栈已满，不能进栈!\n");
            return -1;
        }
    }
    for (i = 0; i < sizeof(b)/sizeof(b[0]); i++) {
        if (PushStack(&S, b[i], 1) == 0) {
            printf("栈已满，不能进栈!\n");
            return -1;
        }
    }
    
    if (GetTop(S, &e1, 0) == 0) {
        printf("栈已空\n");
        return -1;
    }
    if (GetTop(S, &e2, 1) == 0) {
        printf("栈已空\n");
        return -1;
    }
    
    printf("左端栈的栈顶元素是: %c, 右端栈的栈顶元素是: %c\n", e1, e2);
    printf("左端栈的出栈的元素次序是: ");
    i = 0;
    while (! StackEmpty(S, 0)) {
        PopStack(&S, &e1, 0);
        printf("%4c", e1);
    }
    printf("\n");
    printf("右端栈的出栈的元素次序是: ");
    i = 0;
    while (! StackEmpty(S, 1)) {
        PopStack(&S, &e2, 1);
        printf("%4c", e2);
    }
    printf("\n");
    
    return 0;
}