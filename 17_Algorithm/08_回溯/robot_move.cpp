
// 13 机器人的运动范围

// 问题:
// 地上有一个 m 行 n 列的方格。一个机器人从坐标 (0,0) 的格子开始移动，它每次可以
// 向左、右、上、下移动一格，但不能进入行坐标和列坐标的数位之和大于 k 的格子。
// 例如，当 k 为 18 时，机器人能够进入方格(35,37)，因为 3 + 5 + 3 + 7 = 18。但
// 它不能进入方格 (35,38), 因为 3 + 5 + 3 + 8 = 19 。
// 问该机器人能够到达多少格子?

// 分析:
// 回溯

#include <stdio.h>
#include <string.h>

bool check_sum(int row, int col, int k)
{
    int sum = 0;
    while (row > 0) {
        sum += row % 10;
        row /= 10;
    }

    while (col > 0) {
        sum += col % 10;
        col /= 10;
    }

    return sum <= k;
}

int _robot_move(int rows, int cols, int row, int col, int k, bool* visited)
{
    if (row >= 0 & col >= 0 && row < rows && col < cols
        && ! visited[row * cols + col]
        && check_sum(row, col, k))
    {
        visited[row * cols + col] = true;

        return 1 + _robot_move(rows, cols, row, col - 1, k, visited) +
                   _robot_move(rows, cols, row - 1, col, k, visited) +
                   _robot_move(rows, cols, row, col + 1, k, visited) +
                   _robot_move(rows, cols, row + 1, col, k, visited);
    }

    return 0;
}

int robot_move(int rows, int cols, int k)
{
    // assert(rows > 0 && cols > 0 && k > 0);

    bool* visited = new bool[rows * cols];
    memset(visited, 0, rows * cols);

    int count = _robot_move(rows, cols, 0, 0, k, visited);

    delete visited;

    return count;
}

int main()
{
    printf("%d\n", robot_move(10, 10, 5));  // 21
    printf("%d\n", robot_move(20, 20, 15)); // 359
    printf("%d\n", robot_move(1, 100, 10)); // 29

    return 0;
}