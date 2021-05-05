
#include <stdio.h>

#define STACKSIZE 100

typedef struct {
    DataType stack[STACKSIZE];
    int top;
} SeqStack;

/**
 * 栈的初始化操作
 */
void InitStack(SeqStack * S)
{
    S->top = 0;
}
/**
 * 判断栈是否为空
 */
int StackEmpty(SeqStack S)
{
    if (S.top == 0)
        return 1;
    else
        return 0;
}
/**
 * 取栈顶元素操作
 */
int GetTop(SeqStack S, DataType * e)
{
    if (S.top <= 0) {
        printf("栈已经空!\n");
        return 0;
    } else {
        *e = S.stack[S.top - 1];
        return 1;
    }
}
/**
 * 进栈操作
 */
int PushStack(SeqStack * S, DataType e)
{
    if (S->top >= STACKSIZE) {
        printf("栈已满，不能进栈!\n");
        return 0;
    } else {
        S->stack[S->top] = e;
        S->top++;
        return 1;
    }
}
/**
 * 出栈操作
 */
int PopStack(SeqStack * S, DataType * e)
{
    if (S->top == 0) {
        printf("栈已经没有元素，不能出栈!\n");
        return 0;
    } else {
        S->top--;
        *e = S->stack[S->top];
        return 1;
    }
}
/**
 * 返回栈的长度操作
 */
int StackLength(SeqStack S)
{
    return S.top;
}
/**
 * 清空栈的操作
 */
void ClearStack(SeqStack * S)
{
    S->top = 0;
}