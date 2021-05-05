
#include <assert.h>

typedef struct Node
{
    DataType data;
    struct Node * next;
} LStackNode, * LinkStack;

/**
 * 初始化操作
 */
void InitStack(LinkStack * top)
{
    *top = (LStackNode*)malloc(sizeof(LStackNode));
    assert(*top != NULL);
    
    (*top)->next = NULL;
}
/**
 * 栈是否为空
 * 就是通过判断头结点的指针域是否为空
 */
int StackEmpty(LinkStack top)
{
    if (top->next == NULL)
        return 1;
    else
        return 0;
}
/**
 * 进栈操作
 * 在链表的第一个有效节点之前插入一个新节点
 */
int PushStack(LinkStack top, DataType e)
{
    LStackNode * p;
    p = (LStackNode*)malloc(sizeof(LStackNode));
    assert(p != NULL);
    
    p->data = e;
    p->next = top->next;
    top->next = p;
    
    return 1;
}
/**
 * 出栈操作
 * 将单链表中的第一个有效节点删除
 */
int PopStack(LinkStack top, DataType * e)
{
    LStackNode * p;
    p = top->next;      // 第一个有效节点
    if (p == NULL) {
        printf("栈已空");
        return 0;
    }
    top->next = p->next;
    *e = p->data;
    free(p);
    
    return 1;
}
/**
 * 取栈顶元素
 */
int GetTop(LinkStack top, DataType * e)
{
    LStackNode * p;
    p = top->next;
    if (p == NULL) {
        printf("栈已空");
        return 0;
    }
    *e = p->data;
    
    return 1;
}
/**
 * 求表长操作
 */
int StackLength(LinkStack top)
{
    LStackNode * p;
    int count = 0;
    
    p = top->next;
    
    while (p != NULL) {
        p = p->next;
        count++;
    }
    
    return count;
}
/**
 * 销毁链栈操作
 */
void DestroyStack(LinkStack top)
{
    LStackNode * p, * q;
    
    p = top;
    
    while (p != NULL) {
        q = p;
        p = p->next;
        free(q);
    }
}