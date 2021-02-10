
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <map>

#define SIZE_FOR_TEST      211

int main ()
{
    /** 桶长素数测试 */
    {
        printf("===== 桶长素数测试 =====\n");
        
        std::unordered_map<int, int> intmap;
        
        intmap.rehash(SIZE_FOR_TEST);
        
        printf("bucket_count=%ld\n", intmap.bucket_count());
        printf("\n");
    }
    
    /** 哈希键测试 */
    {
        printf("===== 哈希键测试 =====\n");
        
        std::unordered_map<int, int> intmap;
        
        printf("int=12345's hash key is %ld\n", intmap.hash_function()(12345));
        printf("\n");
    }
    
    /** 哈希桶内键数量的测试 */
    {
        printf("===== 哈希桶内键数量的测试 =====\n");
        
        std::unordered_map<int, int> intmap;
        
        intmap.rehash(SIZE_FOR_TEST);
        
        intmap[4] = 40;
        intmap[128] = 1280;
        intmap[4 + 211] = (4 + 211) * 10;
        intmap[4 + 211 * 101] = (4 + 211 * 101) * 10;
        
        size_t i;
        std::map<int, int> index_count;
        for (i = 0; i < intmap.bucket_count(); i++) {
            if (intmap.bucket_size(i)) {
                index_count[i] = intmap.bucket_size(i);
            }
        }
        
        for (auto it = index_count.begin(); it != index_count.end(); it++) {
            printf("index=%d, count=%d\n", it->first, it->second);
        }
        printf("\n");
    }
    
    return 0;
}