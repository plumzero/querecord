
#include <iostream>
#include <unordered_map>

int main ()
{
    {
        std::unordered_map<int, int> umap;
        
        umap[4] = 40;
        umap[128] = 1280;
        umap[4 + 211] = (4 + 211) * 10;
        umap[4 + 211 * 101] = (4 + 211 * 101) * 10;
        
        
        auto iter = umap.find(4);
        if (iter != umap.end()) {
            std::cout << "Find! value is " << iter->second << std::endl;
        }
    }

    return 0;
}