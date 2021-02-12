
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

/**
    可能的实现
    版本一
    template<class InputIt, class OutputIt, class UnaryOperation>
    OutputIt transform(InputIt first1, InputIt last1, OutputIt d_first, 
                       UnaryOperation unary_op)
    {
        while (first1 != last1) {
            *d_first++ = unary_op(*first1++);
        }
        return d_first;
    }
    版本二
    template<class InputIt1, class InputIt2, 
             class OutputIt, class BinaryOperation>
    OutputIt transform(InputIt1 first1, InputIt1 last1, InputIt2 first2, 
                       OutputIt d_first, BinaryOperation binary_op)
    {
        while (first1 != last1) {
            *d_first++ = binary_op(*first1++, *first2++);
        }
        return d_first;
    }
    
    说明:
        1. 将 [first1, last1) 中的元素进行谓词操作，并将操作后的结果存储到始于
           d_first 的另一范围。
        2. 仅对版本二作示例
    
    关键词：
        1. 输入迭代器 输出迭代器
        2. 一元谓词 二元谓词，返回类型为输出迭代器同类型
        3. 函数返回值: 输出迭代器
 */

struct ToUpper {
    char operator()(char c) { return std::toupper(c); }
};

char to_lower(char c) { return std::tolower(c); }

/** 字符串转大写(原地转换) */
int main()
{
    std::string s("Hello World!");
    
    /** [1] function object */
    std::transform(s.begin(), s.end(), s.begin(), ToUpper());
    std::cout << s << std::endl;
    
    /** [2] function pointer */
    std::transform(s.begin(), s.end(), s.begin(), to_lower);
    std::cout << s << std::endl;

    /** [3] lambda expression */
    std::transform(s.begin(), s.end(), s.begin(), [](char c) {
        return std::toupper(c);
    });
    std::cout << s << std::endl;

    return 0;
}