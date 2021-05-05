
#include <stdio.h>

#define MAXSIZE 100

/** 递归 */
int fact1(int n)
{
    if (n == 1)
        return 1;
    else
        return n * fact1(n - 1);
}
/** 非递归 */
int fact2(int n)
{
    int s[MAXSIZE][2], top = -1;
    /** 栈顶指针加 1, 工作记录入栈 */
    top++;
    s[top][0] = n;  // 记录每一层的参数
    s[top][1] = 0;  // 记录每一层的结果返回值
    
    do {
        if (s[top][0] == 1) // 递归出口，当第一维数组元素值不为 0, 说明已经有结果返回
            s[top][1] = 1;
        
        if (s[top][0] > 1 && s[top][1] == 0) {  // 入栈，模拟函数调用
            top++;
            s[top][0] = s[top - 1][0] - 1;
            s[top][1] = 0;
        }
        
        if (s[top][1] != 0) {   // 出栈，模拟函数调用返回
            s[top - 1][1] = s[top][1] * s[top - 1][0];
            top--;
        }
    } while (top > 0);
    
    return s[0][1];
}

int main()
{   
    int f, n;
    
    printf("输入一个正整数(n<15): ");
    scanf("%d", &n);
    
    printf("递归实现 n 的阶乘:");
    f = fact1(n);
    printf("%d! = %4d\n", n, f);
    
    printf("非递归实现 n 的阶乘:");
    f = fact2(n);
    printf("%d! = %4d\n", n, f);
    
    return 0;
}