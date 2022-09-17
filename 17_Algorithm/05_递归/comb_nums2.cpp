
// 问题: 从一组自然数中任选 r 个数的所有组合数

// 例如，给出 [ 6, 1, 3, 5, 7 ], r = 3, 则输出结果如下:
// 7 5 3 
// 7 5 1 
// 7 5 6 
// 7 3 1 
// 7 3 6 
// 7 1 6 
// 5 3 1 
// 5 3 6 
// 5 1 6 
// 3 1 6

// 分析:
// 本题也可以化为一个上台阶问题，只不过台阶的编号为数组各元素对应的索引

// 延伸: 如果数组中存在重复的数字，可以先通过一次循环将其唯一，之后对剩余的数组元素进行处理

#include <stdio.h>
#include <vector>

std::vector<int> _stack;

void print(int a[])
{
    for (auto& ele : _stack) {
        printf("%d ", a[ele]);
    }
    printf("\n");
}

void step(int n, int r, int a[])
{
    if (r == 0) {
        print(a);
        return ;
    }

    if (_stack.size() > 0 && r > _stack.back()) {
        return ;
    }

    for (int i = n; i >= 0; i--) {
        _stack.push_back(i);
        step(i - 1, r - 1, a);
        _stack.pop_back();
    }
}

int main()
{
    int a[] = { 6, 1, 3, 5, 7 };
    int len = sizeof(a) / sizeof(int);

    step(len - 1, 3, a);

    return 0;
}