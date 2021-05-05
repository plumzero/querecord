
#include <stdio.h>
#include <stdlib.h>

#define N 8

#define C  -1

int main()
{
    {
        printf("上三角矩阵测试:\n");
        
        int A[N][N];
        int i, j, k;
            
        // 初始化
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                A[i][j] = -1;
            }
        }
        
        // 构造上三角矩阵
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                if (i <= j) {
                    A[i][j] = rand() % 100;
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
        
        // 存储上三角矩阵
        int a[N * (N + 1) / 2 + 1] = { 0 };
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                if (i <= j) {
                    k = i * (2 * N - i + 1) / 2 + j - i;
                    a[k] = A[i][j];
                } else {
                    a[N * (N + 1) / 2] = C;
                }
            }
        }    
        
        for (k = 0; k < (int)(sizeof(a) / sizeof(int)); k++) {
            printf("%2d ", a[k]);
            if ((k + 1) % N == 0)
                printf("\n");
        }
        printf("\n\n");
        
        i = 4, j = 5;
        printf("A[%d][%d]=%d\n", i, j, a[i * (2 * N - i + 1) / 2 + j - i]);
    }
    
    {
        printf("\n下三角矩阵测试:\n");
        int A[N][N];
        int i, j, k;
            
        // 初始化
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                A[i][j] = -1;
            }
        }
        
        // 构造下三角矩阵
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                if (i >= j) {
                    A[i][j] = rand() % 100;
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
        
        // 存储下三角矩阵
        int a[N * (N + 1) / 2 + 1] = { 0 };
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                if (i >= j) {
                    k = i * (i + 1) / 2 + j;
                    a[k] = A[i][j];
                } else {
                    a[N * (N + 1) / 2] = C;
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
    }
    
    return 0;
}