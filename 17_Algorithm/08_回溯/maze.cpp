
#include <stdio.h>
#include <vector>

// 迷宫字符含义:
//  '*' 墙
//  ' ' 路径
//  '@' 入口
//  '#' 出口
//  'o' 路线
//  'x' 尝试但没有走通的路径 
char MAZE[10][12] = {
    '@', '*', '*', '*', '*', ' ', ' ', ' ', '*', '*', '*', '*',
    '*', ' ', ' ', ' ', '*', '*', '*', '*', '*', '*', '*', '*',
    '*', '*', '*', ' ', '*', '*', ' ', ' ', ' ', ' ', '*', '*',
    '*', '*', '*', ' ', '*', '*', ' ', '*', '*', ' ', '*', '*',
    '*', '*', '*', ' ', ' ', ' ', ' ', '*', '*', ' ', '*', '*',
    '*', '*', '*', ' ', '*', '*', ' ', '*', '*', ' ', '*', '*',
    '*', '*', '*', ' ', '*', '*', ' ', '*', '*', ' ', '*', '*',
    '*', '*', '*', ' ', '*', '*', ' ', ' ', '*', ' ', '*', '*',
    '*', '*', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', '*',
    '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '#'
};

struct Point
{
    int x;
    int y;

    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    bool operator==(const Point& P) {
        return x == P.x && y == P.y;
    }
    bool operator!=(const Point& P) {
        return x != P.x || y != P.y;
    }
};


int main()
{
    // 路线
    std::vector<Point> _path;   // 模拟栈
    // 入口点
    Point _in(1, 1);
    // 出口点
    Point _out(8, 10);
    // 当前点
    Point _cur;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 12; j++) {
            printf("%2c", MAZE[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    _cur = _in;

    while (_cur != _out) {
        MAZE[_cur.x][_cur.y] = 'o';
        _path.push_back(_cur);
        if (MAZE[_cur.x - 1][_cur.y] == ' ') {
            _cur.x -= 1;
        } else if (MAZE[_cur.x + 1][_cur.y] == ' ') {
            _cur.x += 1;
        } else if (MAZE[_cur.x][_cur.y - 1] == ' ') {
            _cur.y -= 1;
        } else if (MAZE[_cur.x][_cur.y + 1] == ' ') {
            _cur.y += 1;
        } else {
            MAZE[_cur.x][_cur.y] = 'x';
            _path.pop_back();
            _cur = _path.back();
        }
    }

    // 出口点补上
    if (_cur == _out) {
        MAZE[_cur.x][_cur.y] = 'o';
        _path.push_back(_cur);
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 12; j++) {
            printf("%2c", MAZE[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for (const auto p : _path) {
        printf("(%d,%d) ", p.x, p.y);
    }
    printf("\n");

    return 0;
}