
// 问题: 从自然数 1~n 中任选 r 个数的所有组合数

// 例如，给出 n = 5, r = 3, 则输出结果如下:
// 5 4 3 
// 5 4 2 
// 5 4 1 
// 5 3 2 
// 5 3 1 
// 5 2 1 
// 4 3 2 
// 4 3 1 
// 4 2 1 
// 3 2 1 

// 分析: 
// 本题也可以看作一个上台阶问题，不同的是这里要求最多上 r 次
// 将每个台阶进行编号，假设分别为 n, n-1, n-2, ..., 3, 2, 1
// 假设第一次跳到了 k 阶上，那么下一次就得从 [k-1,...,2,1] 中选一阶跳，如此

#include <stdio.h>
#include <vector>

std::vector<int> _stack;

void step(int n, int r)
{
    if (r == 0) {
        for (auto& item : _stack) {
            printf("%d ", item);
        }
        printf("\n");
        return ;
    }
    // if (r > 0 && _stack.size() > 0 && _stack.back() == 1) {
    //     return ;
    // }
    // 上面注释掉的代码是首版写的。
    // 在台阶中最后一阶编号为 1, 如果待跳的次数 r 大于等于最后一个入栈的台阶编号，那么无论如何
    // 也不会跳满 r 个台阶的，此时应该及早退出
    if (_stack.size() > 0 && r >= _stack.back()) {
        return ;
    }

    for (int i = n; i >= 1; i--) {
        _stack.push_back(i);
        step(i - 1, r - 1);
        _stack.pop_back();
    }
}

int main()
{
    step(5, 3);

    return 0;
}