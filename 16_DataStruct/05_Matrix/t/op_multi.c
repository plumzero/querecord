
#include <stdio.h>

// 二维数组表示矩阵
void dim2()
{
    int a[2][3] = { {1, 2, 3}, { 4, 5, 6} };
    int b[3][4] = { {12, 11, 10, 9}, {8, 7, 6, 5}, {4, 3, 2, 1} };
    int c[2][4] = { 0 };

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 3; k++)
                c[i][j] += a[i][k] * b[k][j];

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
}

// 一维数组表示矩阵
void dim1()
{
    int a[6] = { 1, 2, 3, 4, 5, 6 };    // 2 × 3
    int b[12] = { 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };  // 3 × 4
    int c[8] = { 0 };   // 2 × 4
    
    const int rows = 2;
    const int cols = 4;
    const int nums = 3;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            for (int k = 0; k < nums; k++)
                c[i * cols + j] += a[i * nums + k] * b[k * cols + j]; 

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", c[i * cols + j]);
        }
        printf("\n");
    }
}

int main()
{
    dim2();

    printf("\n");

    dim1();

    return 0;
}