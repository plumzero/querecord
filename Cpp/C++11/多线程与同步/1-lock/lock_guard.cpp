
#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

std::mutex mtx;
std::map<std::thread::id, int> use_map;     /** 统计使用的线程次数 */

void add(int& num, int& sum)
{
    while (true) {
        std::lock_guard<std::mutex> locker(mtx);
        
        use_map[std::this_thread::get_id()]++;
        
        if (num < 10000) {
            num += 1;
            sum += num;
        } else {
            break;
        }
    }
}

int main()
{
    int sum = 0;
    int num = 0;
    std::vector<std::thread> vec;
    int i;
    for (i = 0; i < 20; i++) {
        std::thread th = std::thread(add, std::ref(num), std::ref(sum));
        vec.emplace_back(std::move(th));
    }
    
    std::for_each(vec.begin(), vec.end(), std::mem_fn(&std::thread::join));
    
    std::cout << "sum=" << sum << std::endl;
    
    int counter = 0;
    for (const auto& ele : use_map) {
        std::cout << ele.first << " : " << ele.second << std::endl;
        counter += ele.second;
    }
    std::cout << "counter=" << counter << std::endl;
    
    return 0;
}