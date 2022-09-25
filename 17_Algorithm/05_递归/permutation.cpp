
// 问题:
// 给定一个数组，数组内元素两两不等，求该数组的全排列
// 例如数组 [1,2,3]，它一共有 6 种全排列，分别是:
// 1 2 3 
// 1 3 2 
// 2 1 3 
// 2 3 1 
// 3 2 1 
// 3 1 2

// 分析:
// 假设数组长度为 n, 元素为 a1,a2,...,an, 如果想要求这 n 个数组元素的全排列，那就相当于求
// a1 固定时，a2,a3,...,an 的全排列集合; a2 固定时，a1,a3,...,an 的全排列集合;... an 固定时，a1,a2,...,a(n-1) 的全排列集合的汇总
// 而每个集合又可以分为更小的集合...

#include <stdio.h>

void print(int a[], int len)
{
    for (int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void permutation(int a[], int start, int end)
{
    if (start == end) {
        print(a, end + 1);
        return ;
    }

    for (int i = start; i <= end; i++) {
        int tmp = a[start];
        a[start] = a[i];
        a[i] = tmp;
        permutation(a, start + 1, end);
        tmp = a[start];
        a[start] = a[i];
        a[i] = tmp;
    }
}

// 思考: 如果给定数组中存在重复元素呢?
// 分析:
// 给定数组如果存在重复元素，那么就不交换了。不过得排除 start 那个元素
// 有点问题...
void permutation_repeat(int a[], int start, int end)
{
    if (start == end) {
        print(a, end + 1);
        return ;
    }

    for (int i = start; i <= end; i++) {
        if (i == start || a[i] != a[start]) {
            int tmp = a[start];
            a[start] = a[i];
            a[i] = tmp;
            permutation_repeat(a, start + 1, end);
            tmp = a[start];
            a[start] = a[i];
            a[i] = tmp;
        }
    }
}

int main()
{
    {
        int a[] = { 1, 2, 3 };
        int len = sizeof(a) / sizeof(int);

        permutation(a, 0, len - 1);
        printf("\n");
    }

    {
        int a[] = { 1, 2, 2 };
        int len = sizeof(a) / sizeof(int);

        permutation_repeat(a, 0, len - 1);
    }

    return 0;
}