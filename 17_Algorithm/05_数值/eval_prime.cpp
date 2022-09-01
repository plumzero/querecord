
// 求 1 ~ 50 之间的质数

// 埃拉托斯尼斯筛选法

// 了解这种思想

#include <stdio.h>

#define N (50)

int main()
{
    int numbers[N + 1] = { 0 };
    
    printf("该范围内质数有: ");
    for (int i = 2; i <= N; i++) {      // 从最小质数 2 开始。也可以只比较到 sqrt(N) 就可以了
        if (numbers[i] == 0) {
            printf("%d ", i);
            for (int j = 2 * i; j <= N; j += i) {   // j 从 i 开始是没必要的，所以从 2 * i 开始，之后每次递增 i，形成整倍
                numbers[j] = 1;
            }
        }
    }
    printf("\n");

    return 0;
}
