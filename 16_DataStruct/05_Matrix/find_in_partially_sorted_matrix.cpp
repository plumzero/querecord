
// 04 二维数组的查找

// 问题:
// 在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。
// 要求输入一个这样的二维数组和一个整数，判断数组中是否含有该整数。

// 分析一: 
// 一种方法是采用递归形式实现，比较直观。如下:

bool _find(int* matrix, int rows, int cols, int number, int row, int col)
{
    // assert(matrix != nullptr && rows > 0 && cols > 0);

    if (row >= 0 && col >= 0 && row < rows && col < cols) {
        if (matrix[row * cols + col] == number) {
            return true;
        }

        return _find(matrix, rows, cols, number, row + 1, col) ||
               _find(matrix, rows, cols, number, row, col + 1);
    }

    return false;
}

// 因为矩阵是有序的，所以也可以通过判断在适当的时候返回
bool _find2(int* matrix, int rows, int cols, int number, int row, int col)
{
    // assert(matrix != nullptr && rows > 0 && cols > 0);

    if (row >= 0 && col >= 0 && row < rows && col < cols) {
        if (matrix[row * cols + col] == number) {
            return true;
        }

        if (matrix[row * cols + col] > number) {
            return false;
        }

        return _find2(matrix, rows, cols, number, row + 1, col) ||
               _find2(matrix, rows, cols, number, row, col + 1);
    }

    return false;
}

bool find(int* matrix, int rows, int cols, int number)
{
    return _find2(matrix, rows, cols, number, 0, 0);
}

// 分析二:
// 一种是观察数组，从右上角的值开始与给定值比较，如果比给定值大，则左移一列比较。如果比给定值小，则下移一行比较。
// 重复此操作，直到找到给定值或者 行/列索引同时为 0

// 在实现上，原本想用两个 for 循环进行，这需要在内部根据条件进行 break。如果改成两个 while 循环，同样也如此。
// 不如使用一个 while 循环

bool find3(int* matrix, int rows, int cols, int number) {
    // assert(matrix != nullptr && rows > 0 && cols > 0);

    int row = 0;
    int col = cols - 1;
    while (row < rows && col >= 0) {
        if (matrix[row * cols + col] == number) {
            return true;
        } else if (matrix[row * cols + col] > number) {
            col--;
        } else {
            row++;
        }
    }

    return false;
}


#include <stdio.h>

int main()
{
    {
        int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
        int number = 15;
        printf("%d\n", find((int*)matrix, 4, 4, number));
    }

    {
        int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
        int number = 5;
        printf("%d\n", find((int*)matrix, 4, 4, number));
    }

    {
        int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
        int number = 1;
        printf("%d\n", find((int*)matrix, 4, 4, number));
    }

    {
        int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
        int number = 15;
        printf("%d\n", find3((int*)matrix, 4, 4, number));
    }

    {
        int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
        int number = 5;
        printf("%d\n", find3((int*)matrix, 4, 4, number));
    }

    {
        int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
        int number = 1;
        printf("%d\n", find3((int*)matrix, 4, 4, number));
    }

    return 0;
}