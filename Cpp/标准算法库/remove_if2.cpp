
#include <iostream>
#include <vector>
#include <algorithm>

/** 
 * std::remove_if 并不是真的将元素"移除"，而是将不需要移除的元素向前移动，替换要"移除"的元素。
 * 如下，对于向量元素数组:
 *  5, 28, 50, 83, 70, 590, 245, 59, 24
 * 现在要移除其中大于 30 且小于 100 的元素，调用 std::remove_if 后的结果是:
 *  5, 28, 590, 245, 24, 590, 245, 59, 24
 *                        end
 * 尾部迭代器指向第二个 590 元素。
 *
 * 所以如果需要真正移除元素，需要分成两步，第一步调用 std::remove_if, 第二步 erase。
 */
 
int main()
{
    std::vector<int> vi {5, 28, 50, 83, 70, 590, 245, 59, 24};
    
    vi.erase(std::remove_if(vi.begin(), vi.end(), [](int x){ return x > 30 && x < 100; }), vi.end());
    
    for (const auto & ele : vi) {
        std::cout << ele << " ";
    }
    std::cout << std::endl;
    
    return 0;
} 