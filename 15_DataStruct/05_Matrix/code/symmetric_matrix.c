
#include <stdio.h>
#include <stdlib.h>

#define N 8

int main()
{
    int A[N][N];
    int i, j, k;
        
    // 初始化
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = -1;
        }
    }
    
    // 构造对称矩阵
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (A[j][i] == -1) {
                A[i][j] = rand() % 100;
            } else {
                A[i][j] = A[j][i];
            }
        }
    }
    
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%2d ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // 下三角存储矩阵
    int a[N * (N + 1) / 2] = { 0 };
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (i >= j) {
                k = i * (i + 1) / 2 + j;
                a[k] = A[i][j];
            }
        }
    }
    
    
    for (k = 0; k < (int)(sizeof(a) / sizeof(int)); k++) {
        printf("%2d ", a[k]);
        if ((k + 1) % N == 0)
            printf("\n");
    }
    printf("\n\n");
    
    i = 5, j = 4;
    printf("A[%d][%d]=%d\n", i, j, a[i * (i + 1) / 2 + j]);

    i = 4, j = 5;
    printf("A[%d][%d]=%d\n", i, j, a[j * (j + 1) / 2 + i]);
    
    return 0;
}