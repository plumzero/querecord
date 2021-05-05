
#include <stdio.h>
#include <stdlib.h>

#define N 8
#define M 3

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
    
    // 构造 M 对角带状矩阵
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (i == 0 && j < M - 1) {
                A[i][j] = rand() % 100;
            } else if (i == N - 1 && j > N - M) { 
                A[i][j] = rand() % 100;
            } else if (j >= i - (M - 1) / 2 && j < i - (M - 1) / 2 + M) {
                A[i][j] = rand() % 100;
            } else {
                A[i][j] = 0;
            }
        }
    }
    
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%3d ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // 一维数组存储
    int a[M * N - 2] = { 0 };
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (i == 0 && A[i][j] != 0) {
                k = j;
                a[k] = A[i][j];
            } else if (A[i][j] != 0) {
                k = M * i - 1 + j - i + (M - 1) / 2;
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

    return 0;
}