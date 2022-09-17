
// 12 矩阵中的路径

// 问题:
// 请设计一个函数，用来判断在一个矩阵中是否存在一条包含某
// 字符串所有字符的路径。路径可以从矩阵中的任意一格开始，
// 每一步可以在矩阵中向左、右、上、下移动一格。如果一条
// 路径经过了矩阵的某一格，那么该路径不能再次进入该格子。
// 例如，在下面的 3 x 4 矩阵中包含一条字符串 "bfce" 的
// 路径，但矩阵中不包含字符串 "abfb" 的路径。
// a b t g
// c f c s
// j d e h

// 分析:
// 回溯

#include <stdio.h>
#include <string.h>

bool _find_path(char* matrix, int rows, int cols, int row, int col, char* str, int& path_len, bool* visited)
{
    if (str[path_len] == '\0')
        return true;

    bool has_path = false;
    if (row >= 0 && row < rows && col >= 0 && col < cols
        && matrix[row * cols + col] == str[path_len]
        && ! visited[row * cols + col])
    {
        path_len++;
        visited[row * cols + col] = true;
        has_path = _find_path(matrix, rows, cols, row, col - 1, str, path_len, visited)
                || _find_path(matrix, rows, cols, row - 1, col, str, path_len, visited)
                || _find_path(matrix, rows, cols, row, col + 1, str, path_len, visited)
                || _find_path(matrix, rows, cols, row + 1, col, str, path_len, visited);

        if (! has_path) {
            path_len--;
            visited[row * cols + col] = false;
        }
    }

    return has_path;
}

bool find_path(char* matrix, int rows, int cols, char* str)
{
    // assert(matrix != nullptr && rows > 0 && cols > 0 && str != nullptr);

    bool* visited = new bool[rows * cols];
    memset(visited, 0, rows * cols);

    int path_len = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (_find_path(matrix, rows, cols, i, j, str, path_len, visited))
                return true;
        }
    }

    delete visited;

    return false;
}

int main()
{
    {
        char matrix[] = "ABTGCFCSJDEH";
        char str[] = "BFCE";
        printf("%d\n", find_path(matrix, 3, 4, str));
    }

    {
        char matrix[] = "ABTGCFCSJDEH";
        char str[] = "ABFB";
        printf("%d\n", find_path(matrix, 3, 4, str));
    }

    return 0;
}