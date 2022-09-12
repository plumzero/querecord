
// 体会递归化循环

#include <stdio.h>

#define N 100

// 递归实现
int fact1(int n)
{
    if (n == 0)
        return 1;
    return n * fact1(n - 1);
}

// 循环实现
int fact2(int n)
{
    int prod = 1;
    for (; n != 0; n--) {
        prod *= n;
    }
    return prod;
}

// 一维数组模拟函数调用
int fact3(int n)
{
    int stk[N] = { 0 };
    int top = -1;
    int prod = 0;   // 入栈或出栈时，最上面的元素都可能大于 1，所以设置一个标志用作表示入栈或者出栈。这里可以将 prod 作为判断条件，节省了一个变量

    top++;
    stk[top] = n;

    do {
        // 入栈
        if (stk[top] > 1 && prod == 0) {
            top++;
            n -= 1;
            stk[top] = n;
        }

        // 入栈完毕，开始出栈
        if (stk[top] == 1)
            prod = 1;   // 将这里修改为 prod = stk[top]; 执行结果也是一样的，但是改成后者后有出栈的语义，而真正的出栈操作是在下面，所以最好写成 prod = 1
        
        // 出栈
        if (prod != 0) {
            prod *= stk[top];
            top--;
        }
    } while (top >= 0);

    return prod;
}

// 二维数组模拟函数调用
int fact4(int n)
{
    int stk[N][2] = { {0, 0} };
    int top = -1;

    top++;
    stk[top][0] = n;    // 存储入参
    stk[top][1] = 0;    // 存储返回值

    do {
        // 入栈
        if (stk[top][0] > 1 && stk[top][1] == 0) {
            top++;
            n -= 1;
            stk[top][0] = n;
        }
        // 设置出栈
        if (stk[top][0] == 1)
            stk[top][1] = 1;

        // 出栈
        if (stk[top][1] != 0) {
            stk[top - 1][1] = stk[top][1] * stk[top - 1][0];
            top--;
        }

    } while (top > 0);

    return stk[0][1];
}

int main()
{
    printf("fact1(5)=%d\n", fact1(5));
    printf("fact2(5)=%d\n", fact2(5));
    printf("fact3(5)=%d\n", fact3(5));
    printf("fact4(5)=%d\n", fact4(5));

    return 0;
}