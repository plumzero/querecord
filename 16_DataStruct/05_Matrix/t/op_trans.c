
#include <stdio.h>

// 二维数组表示矩阵
void dim2()
{
    int a[3][4] = { {1, 3, 5, 7}, { 9, 11, 13, 15 }, { 17, 19, 21, 23 } };
    int c[4][3] = { 0 };

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
            c[j][i] = a[i][j];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
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
    int c[12] = { 0 };
    
    const int rows = 3;
    const int cols = 4;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            c[j * rows + i] = a[i * cols + j];
        }

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            printf("%d ", c[i * rows + j]);
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