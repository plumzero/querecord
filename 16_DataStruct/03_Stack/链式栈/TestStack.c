
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char DataType;
#include "LinkStack.h"

int main()
{
    LinkStack S;
    
    DataType ch[50] = { 'a', 'b', 'c', 'd', 'e', 'f' }, e, * p;
    
    InitStack(&S);
    
    printf("请输入进栈的字符: \n");
    p = &ch[0];
    
    while (*p) {
        PushStack(S, *p);
        p++;
    }
    
    printf("当前栈顶的元素是: ");
    if (GetTop(S, &e) == 0) {
        printf("栈已空!\n");
        return -1;
    } else {
        printf("%4c\n", e);
    }
    
    printf("当前栈中的元素个数是: %d\n", StackLength(S));
    printf("元素出栈的序列是: ");
    while (! StackEmpty(S)) {
        PopStack(S, &e);
        printf("%4c", e);
    }
    printf("\n");
    
    return 0;
}