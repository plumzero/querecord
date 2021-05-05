
#include <stdio.h>
#include <stdlib.h>

typedef char DataType;

#include "SeqStack.h"

int main()
{
    SeqStack S;
    int i;
    DataType a[] = { 'a', 'b', 'c', 'd', 'e' };
    DataType e;
    
    InitStack(&S);
    for (i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
        if (PushStack(&S, a[i]) == 0) {
            printf("栈已满，不能进栈!\n");
            return -1;
        }
    }
    
    printf("出栈的元素是: ");
    if (PopStack(&S, &e) == 1)
        printf("%4c", e);
    if (PopStack(&S, &e) == 1)
        printf("%4c", e);
    printf("\n");
    
    printf("当前栈顶的元素是: ");
    if (GetTop(S, &e) == 0) {
        printf("栈已空!\n");
        return -1;
    } else {
        printf("%4c\n", e);
    }
    
    if (PushStack(&S, 'f') == 0) {
        printf("栈已满，不能进栈!\n");
        return -1;
    }
    if (PushStack(&S, 'g') == 0) {
        printf("栈已满，不能进栈!\n");
        return -1;
    }
    
    printf("当前栈中的元素个数是: %d\n", StackLength(S));
    printf("元素出栈的序列是: ");
    while (! StackEmpty(S)) {
        PopStack(&S, &e);
        printf("%4c", e);
    }
    printf("\n");
    
    return 0;
}