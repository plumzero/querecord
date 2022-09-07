
// 八皇后问题

#include <stdio.h>

#define N 8

int _queen[N];  // 存放 8 个皇后的列位置(行位置为索引)
int _nums;      // 解的个数

void print()
{
    _nums += 1;
    printf("\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == _queen[j])
                printf("x");
            else
                printf("*");
        }
        printf("\n");
    }
}

// 检测是否遭受攻击
bool is_attack(int row, int col)
{
    for (int i = 0; i < row; i++) {
        
    }

    return false;
}

// 在第 row 行上添加皇后，row 从 0 开始
void add_queen(int row)
{
    for (int j = 0; j < N; j++) {
        if (! is_attack(row, j)) {
            _queen[row] = j;
            if (row == N - 1) // 最后一行
                print();
            else
                add_queen(row + 1);
        }
    }
}

