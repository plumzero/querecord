
// 问题: 某人上台阶，一次可以上 1 级台阶、2 级台阶或 3 级台阶。现有 n 级台阶，输出所有可能的上台阶法。
// 例如有 4 级台阶，输出如下:
//  1 1 1 1
//  1 1 2
//  1 2 1
//  1 3
//  2 1 1
//  2 2
//  3 1

// 这也算是一种类型的题目了

#include <stdio.h>
#include <vector>

std::vector<int> _stack;

void step(int n)
{
    if (n == 0) {
        for (auto ele : _stack) {
            printf("%d ", ele);
        }
        printf("\n");
        return ;
    }

    _stack.push_back(1);
    step(n - 1);
    _stack.pop_back();

    if (n > 1) {
        _stack.push_back(2);
        step(n - 2);
        _stack.pop_back();
    }

    if (n > 2) {
        _stack.push_back(3);
        step(n - 3);
        _stack.pop_back();
    }
}

int main()
{
    step(4);

    return 0;
}