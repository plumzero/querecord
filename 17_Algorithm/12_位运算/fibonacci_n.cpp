
// 利用矩阵规律计算出 fibonacci 数列的第 n 项

// 已知 fibonacci 数列:
//   0 1 1 2 3 5 8 13 21 34 ...
// 求其第 n 项
// F(0) = 0, F(1) = 1,  F(n) = F(n-1) + F(n-2) (n>=2)

/*
    F(n+1)     F(n) + F(n-1)     1,1   F(n)      1,1  1,1  F(n-1)     1,1 n F(1)
   (      ) = ( )             = (   ) (     ) = (   )(   )(      ) = (   ) (    )
    F(n)       F(n)              1,0   F(n-1)    1,0  1,0  F(n-2)     1,0   F(0)
                           1,1
    要想计算第 n 项，只要计算 (   ) 矩阵的 n 次幂就可以了。可以利用快速幂求解
                           1,0

    了解矩阵的乘法运算
 */

#include <stdio.h>
#include <string.h>

int fibonacci_n(int n)
{
    int A[2][2] = { 1, 1, 1, 0 };
    int R[2][2] = { 1, 0, 0, 1 };   // 单位阵

    while (n) {
        if (n & 0x1) {
            // R = R * A;
            int CR[2][2] = { 0 };
            memcpy(CR, R, sizeof(R));
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    int sum = 0;
                    for (int k = 0; k < 2; k++) {
                        sum += CR[i][k] * A[k][j];
                    }
                    R[i][j] = sum;
                }
            }
            // R[0][0] = CR[0][0] * A[0][0] + CR[0][1] * A[1][0];
            // R[0][1] = CR[0][0] * A[0][1] + CR[0][1] * A[1][1];
            // R[1][0] = CR[1][0] * A[0][0] + CR[1][1] * A[1][0];
            // R[1][1] = CR[1][0] * A[0][1] + CR[1][1] * A[1][1];
        }
        // A = A * A;
        int CA[2][2] = { 0 };
        memcpy(CA, A, sizeof(A));
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                int sum = 0;
                for (int k = 0; k < 2; k++) {
                    sum += CA[i][k] * CA[k][j];
                }
                A[i][j] = sum;
            }
        }
        // A[0][0] = CA[0][0] * CA[0][0] + CA[0][1] * CA[1][0];
        // A[0][1] = CA[0][0] * CA[0][1] + CA[0][1] * CA[1][1];
        // A[1][0] = CA[1][0] * CA[0][0] + CA[1][1] * CA[1][0];
        // A[1][1] = CA[1][0] * CA[0][1] + CA[1][1] * CA[1][1];
        n >>= 1;
    }

    return R[1][0] * 1 + R[1][1] * 0;   // f1 = 1, f0 = 0
}

int main()
{
    for (int i = 0; i < 10; i++) {
        printf("%d => %d\n", i, fibonacci_n(i));
    }

    int n = 30;
    printf("%d => %d\n", n, fibonacci_n(n));

    n = 1000000;
    printf("%d => %d\n", n, fibonacci_n(n));

    return 0;
}