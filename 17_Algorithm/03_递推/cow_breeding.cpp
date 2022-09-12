
// 问题: 
// 有一头母牛，每年年初生一头小母牛，每头小母牛从第 3 年起，每年年初也生一头小母牛。
// 求第 n 年时有多少头母牛。

// 将母牛分为四类: 刚生下的母牛，1 年大的母牛，2 年大的母牛，大母牛。某年的数量分别为 x0, x1, x2, x3，则:
//  x3 = x3 + x2
//  x2 = x1
//  x1 = x0
//  x0 = x3

// 初始条件
// x0 = 1
// x1 = 0
// x2 = 0
// x3 = 0

// 说明: 和兔子对繁殖很像，但是在问题叙述上关于生长周期的定义感觉略有不一致，不管这个了，思路都是一样的

#include <stdio.h>

int cow_breeding(int n)
{
    int x0 = 1;
    int x1 = 0;
    int x2 = 0;
    int x3 = 0;
    for (int i = 1; i <= n; i++) {
        x3 = x3 + x2;
        x2 = x1;
        x1 = x0;
        x0 = x3;
    }

    return x0 + x1 + x2 + x3;
}

int main()
{
    for (int i = 1; i <= 20; i++) {
        printf("第 %d 年的母牛数: %d\n", i, cow_breeding(i));
    }

    return 0;
}