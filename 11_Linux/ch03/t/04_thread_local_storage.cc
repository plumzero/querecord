
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

// 收集结果处理
#include <map>

static __thread char _buf[512];
// char buf[512];

std::map<long, std::vector<std::string>> _mvec;

std::vector<std::vector<std::string>> _vvec;

int main()
{
	const int th_num = 5;
	for (int i = 0; i < th_num; i++) {
		
	}

    std::vector<std::thread> vec;
    for (int i = 0; i < 5; i++) {
        std::thread th = std::thread([](){
			for (int j = 0; j < 10; j++) {
				// int n = snprintf(_buf, 512, "%ld-%04d", (long)pthread_self(), j);
				// printf("%d:%s\n", n, _buf);
				int len = snprintf(_buf, 512, "%04d", j);
				_mvec[(long)pthread_self()].emplace_back(std::string(_buf, len));
			}
		});
        vec.emplace_back(std::move(th));
    }
    
    std::for_each(vec.begin(), vec.end(), std::mem_fn(&std::thread::join));
    
	return 0;
}