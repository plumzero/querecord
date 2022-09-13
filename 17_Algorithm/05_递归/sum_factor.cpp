
// 问题: (和式分解)
// 给定一个正整数 n, 输出和为 n 的所有非递增的正整数和式。例如，若 n = 5, 则输出的和式结果如下:
//  5 = 5
//  5 = 4 + 1
//  5 = 3 + 2
//  5 = 3 + 1 + 1
//  5 = 2 + 2 + 1
//  5 = 2 + 1 + 1 + 1
//  5 = 1 + 1 + 1 + 1 + 1

#include <stdio.h>

// 下面是书上的解法，要是硬看的话，也是能看懂的...
// a 数组，用来将数组中的元素传递给被调用函数
// i 表示本次递归调用要分解的数
// k 本次递归调用将要分解出的第 k 个和数
// a 用于存放分解出来的和数，其中 a[k] 存放第 k 步分解出来的和数
void rd(int a[], int i, int k)
{
    for (int j = i; j >= 1; j--) {
        if (j <= a[k-1]) {
            a[k] = j;
            if (j == i) {
                printf("%d=%d", a[0], a[1]);
                for (int p = 2; p <= k; p++) {
                    printf("+%d", a[p]);
                }
                printf("\n");
            } else {
                rd(a, i - j, k + 1);
            }
        }
    }
}

// 这里再提供另外一种更简单的做法，分析如下:
// 这个问题与上台阶问题很像，不妨把它转化为跳台阶问题，一次可以跳 n, n-1, ..., 2, 1 阶，同时加一个限制条件: 前面一次跳的阶数不小于下一次要跳的阶数
// 按照这个思路，可以写出如下代码:
// void step(int n)
// {
//     if (n <= 0) {
//         print();
//         return;
//     }
//     for (int i = n; i >= 1; i--) {
//         _stack.push_back(i);
//         step(n - i);
//         _stack.pop_back();
//     }
// }
// 再在循环中加上限制条件即可
//  if (_stack.size() > 0 && _stack.back() < i) continue;

#include <vector>
#include <algorithm>

std::vector<int> _stack;

void print()
{
    printf("%d=", std::accumulate(_stack.begin(), _stack.end(), 0));
    auto it = _stack.begin();
    printf("%d", *it);
    for (it++; it != _stack.end(); it++) {
        printf("+%d", *it);
    }
    printf("\n");
}

// n 剩余的台阶数量
void step(int n)
{
    if (n <= 0) {
        print();
        return;
    }

    for (int i = n; i >= 1; i--) {
        if (_stack.size() > 0 && _stack.back() < i) continue;
        _stack.push_back(i);
        step(n - i);
        _stack.pop_back();
    }
}

int main()
{
    int a[50] = { 0 };
    int n = 5;
    a[0] = n;
    rd(a, n, 1);

    printf("按跳台阶的思路来:\n");
    step(n);

    return 0;
}