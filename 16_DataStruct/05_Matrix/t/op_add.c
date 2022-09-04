
#include <stdio.h>

// 二维数组表示矩阵
void dim2()
{
    int a[3][4] = { {1, 3, 5, 7}, { 9, 11, 13, 15 }, { 17, 19, 21, 23 } };
    int b[3][4] = { {12, 11, 10, 9}, {8, 7, 6, 5}, {4, 3, 2, 1} };
    int c[3][4] = { 0 };

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
            c[i][j] = a[i][j] + b[i][j];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
}

// 一维数组表示矩阵
// 3 × 4 矩阵
void dim1()
{
    int a[12] = { 1, 3, 5, 7, 9, 11, 13, 15 , 17, 19, 21, 23 };
    int b[12] = { 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    int c[12] = { 0 };
    
    const int rows = 3;
    const int cols = 4;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            int k = i * cols + j;
            c[k] = a[k] + b[k];
        }

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