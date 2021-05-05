

typedef struct
{
    DataType stack[STACKSIZE];
    int top[2];             // 其中， top[0] 和 top[1] 分别是两个栈的栈顶指针
} SSeqStack;

/**
 * 初始化操作
 */
void InitStack(SSeqStack * S)
{
    S->top[0] = 0;
    S->top[1] = STACKSIZE - 1;
}
/**
 * 进栈操作。
 * 同顺序栈相比，要通过一个标志变量 flag 判断是哪个栈要进行进栈操作。
 */
int PushStack(SSeqStack * S, DataType e, int flag)
{
    if (S->top[0] == S->top[1])
        return 0;
    switch (flag)
    {
    case 0:
        S->stack[S->top[0]] = e;
        S->top[0]++;
    break;
    case 1:
        S->stack[S->top[1]] = e;
        S->top[1]--;
    break;
    default:
        return 0;
    }
    return 1;
}
/**
 * 出栈操作
 */
int PopStack(SSeqStack * S, DataType * e, int flag)
{
    switch (flag)
    {
    case 0:
        if (S->top[0] == 0)
            return 0;
        S->top[0]--;
        *e = S->stack[S->top[0]];
    break;
    case 1:
        if (S->top[1] == STACKSIZE - 1)
            return 0;
        S->top[1]++;
        *e = S->stack[S->top[1]];
    break;
    default:
        return 0;
    }
    return 1;
}
/**
 * 获取栈元素
 */
int GetTop(SSeqStack S, DataType * e, int flag)
{
    switch (flag)
    {
    case 0:
        if (S.top[0] == 0)
            return 0;
        *e = S.stack[S.top[0] - 1];
    break;
    case 1:
        if (S.top[1] == STACKSIZE - 1)
            return 0;
        *e = S.stack[S.top[1] + 1];
    break;
    default:
        return 0;
    }
    return 1;
}
/**
 * 判断栈是否为空
 */
int StackEmpty(SSeqStack S, int flag)
{
    switch (flag)
    {
    case 0:
        if (S.top[0] == 0)
            return 1;
    break;
    case 1:
        if (S.top[1] == STACKSIZE - 1)
            return 1;
    break;
    default:
        return 0;
    }
    return 0;
}