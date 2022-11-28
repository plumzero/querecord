
#include <stdio.h>
#include <iostream>
#include <unordered_map>

// 定义关于时分秒字符串(hhmmss)的哈希
// 关键点有两个:
//  1. 哈希表长度要超过 86400
//  2. 一个合适的哈希函数

namespace std {
    template<>
    struct hash<const std::string> {
        size_t operator()(const std::string hhmmss) const {
            int val = std::atoi(hhmmss.c_str());
            int sec = val % 100;
            val /= 100;
            int min = val % 100;
            int hour = val / 100;
            return hour * 3600 + min * 60 + sec;
        }
    };
}

int main()
{
    std::unordered_map<std::string, int, std::hash<const std::string>> hash_map;
    hash_map.rehash(86413);
    
    int tick = 0;
    char buf[8] = { 0 };   // 分配内存长度必须要大于 6
    int ret = 0;
    for (int h = 0; h < 24; h++) {
        for (int m = 0; m < 60; m++) {
            for (int s = 0; s < 60; s++) {
                ret = snprintf(buf, sizeof(buf), "%02d%02d%02d", h, m, s);
                if (ret != 6) {
                    std::cout << "unexpected at snprintf" << std::endl;
                    return -1;
                }
                hash_map.insert(std::make_pair(std::string(buf, ret), h * 3600 + m * 60 + s));
                tick++;
            }
        }
    }

    if (tick != 24 * 60 * 60) {
        std::cout << "unexpected ticks: " << tick << "!=" << "86400" << std::endl;
        return -1;
    }

    // check
    for (int h = 0; h < 24; h++) {
        for (int m = 0; m < 60; m++) {
            for (int s = 0; s < 60; s++) {
                ret = snprintf(buf, sizeof(buf), "%02d%02d%02d", h, m, s);
                if (ret != 6) {
                    std::cout << "unexpected at snprintf" << std::endl;
                    return -1;
                }
                const std::string key = std::string(buf, ret);
                int hash_key = hash_map.hash_function()(key);
                if (hash_map[key] != hash_key) {
                    std::cout << "unexpected result: " << "key=" << key << "," << hash_map[key] << "!=" << hash_key << std::endl;
                    return -1;
                }
            }
        }
    }

    std::cout << "test success" << std::endl;

    return 0;
}