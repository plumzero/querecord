
// 17 打印从 1 到最大的 n 位数

// 问题:
// 输入数字 n, 按顺序打印出从 1 到最大的 n 位十进制数。
// 比如输入 3, 则打印出 1,2,3,...998,999

// 分析:
// 首先要考虑到大数，所以不能采用对内建类型进行循环这种打印方式
// 其次要考虑应该怎样终止

// 可以分配一个长度为 n+1 的字符数组，末尾置 '\0', 其余位初始化为 '0'，然后执行自增操作后打印。

// 为了清晰，宜实现为两个函数

#include <stdio.h>
#include <string.h>

bool increment(char* number)
{
    int len = -1;
    while (number[++len]);

    bool is_overflow = false;
    int take_over = 0;
    for (int i = len - 1; i >= 0; i--) {
        int sum = number[i] - '0' + take_over;
        if (i == len - 1)
            sum++;
        if (sum >= 10) {
            if (i == 0) {
                is_overflow = true;
            } else {
                number[i] = '0' + sum - 10;
                take_over = 1;
            } 
        } else {
            number[i] = '0' + sum;
            take_over = 0;
            break;
        }
    }

    return is_overflow;
}

void print(char* number)
{
    char* pch = number;
    while (*pch == '0') pch++;
    printf("%s\n", pch);
}

void func(int n)
{
    char* number = new char[n + 1];
    memset(number, '0', n + 1);
    number[n] = '\0';
    
    while (!increment(number)) {
        print(number);
    }    

    delete number;
}

int main()
{
    func(2);

    return 0;
}
