
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <map>

#define SIZE_FOR_TEST      211

int main ()
{
    // bucket_count: 返回桶的数量
    // bucket_size: 返回参数索引指定的桶中的元素个数
    // bucket:
    {
        std::unordered_map<int, int> umap;
        
        printf("before rehash, bucket count: %lu\n", umap.bucket_count());
        
        umap.rehash(SIZE_FOR_TEST);
        printf("after rehash, bucket count: %lu\n", umap.bucket_count());
        
        umap[4] = 40;
        umap[128] = 1280;
        umap[4 + 211] = (4 + 211) * 10;
        umap[4 + 211 * 101] = (4 + 211 * 101) * 10;
        
        std::map<int, int> index_count;
        for (size_t i = 0; i < umap.bucket_count(); i++) {
            if (umap.bucket_size(i)) {
                index_count[i] = umap.bucket_size(i);
            }
        }
        
        for (auto it = index_count.begin(); it != index_count.end(); it++) {
            printf("bucket %d has %d element(s)\n", it->first, it->second);
        }
        
        size_t index = umap.bucket(128);
        printf("key 128's index is %lu in the bucket\n", index);
        printf("\n");
    }
    
    // bucket_size: 桶中元素个数
    {
        std::unordered_map<int, int> umap;
        
        umap.rehash(SIZE_FOR_TEST);
        
        umap[4] = 40;
        umap[128] = 1280;
        umap[4 + 211] = (4 + 211) * 10;
        umap[4 + 211 * 101] = (4 + 211 * 101) * 10;
        
        size_t i;
        std::map<int, int> index_count;
        for (i = 0; i < umap.bucket_count(); i++) {
            if (umap.bucket_size(i)) {
                index_count[i] = umap.bucket_size(i);
            }
        }
        
        for (auto it = index_count.begin(); it != index_count.end(); it++) {
            printf("index %d has %d element(s)\n", it->first, it->second);
        }
        printf("\n");
    }
    
    // 某个桶索引所在位置中的元素列表
    {
        std::unordered_map<int, int> umap;
        
        umap.rehash(SIZE_FOR_TEST);
        
        umap[4] = 40;
        umap[128] = 1280;
        umap[4 + 211] = (4 + 211) * 10;
        umap[4 + 211 * 101] = (4 + 211 * 101) * 10;
        
        for (auto iter = umap.begin(4); iter != umap.end(4); iter++) {
            printf("element at index %d is %d\n", iter->first, iter->second);
        }
        printf("\n");
    }
    
    return 0;
}