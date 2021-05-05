
#include <iostream>
#include <algorithm>
#include <vector>

int main ()
{
    std::vector<int> v{10, 20, 30, 5, 15};

    /** 创建堆 */
    std::make_heap(v.begin(),v.end());
    std::cout << "initial max heap   : " << v.front() << '\n';

    /** 新增 */
    v.push_back(99);
    std::push_heap (v.begin(),v.end());
    std::cout << "max heap after push: " << v.front() << '\n';

    /** 弹出 */
    std::pop_heap (v.begin(),v.end()); v.pop_back();
    std::cout << "max heap after pop : " << v.front() << '\n';

    std::cout << "element in priority queue after sorted range :";
    for (unsigned i = 0; i < v.size(); i++)
        std::cout << ' ' << v[i];
    std::cout << std::endl;

    std::sort_heap (v.begin(),v.end());

    std::cout << "element in vector after sorted range :";
    for (unsigned i = 0; i < v.size(); i++)
        std::cout << ' ' << v[i];
    std::cout << std::endl;

    return 0;
}