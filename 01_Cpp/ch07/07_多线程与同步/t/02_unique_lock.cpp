
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <iostream>
#include <algorithm>

#include <map>
#include <chrono>

std::mutex mtx;
std::condition_variable cond;
std::map<std::thread::id, int> use_map;     /** 统计使用的线程次数 */

void add(int& num, int& sum)
{
    while (true) {
        /** 必须要延迟上锁，因为锁可能被其他线程所用。而 std::unique_lock 对处于加锁
         *  状态的锁再次加锁时，会报系统异常。
         */
        std::unique_lock<std::mutex> locker(mtx, std::defer_lock);
        if (locker.try_lock()) {
            /** 成功上锁 */
        } else {
            /** 继续下一次尝试 */
            continue;
        }
        use_map[std::this_thread::get_id()]++;
        
        if (num < 10000) {
            num += 1;
            sum += num;
            locker.unlock();    // 2. 退出关键区后立即释放锁
        } else {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));  // 3. 退出关键区后立即释放锁，同时休眠一段时间模拟工作场景
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