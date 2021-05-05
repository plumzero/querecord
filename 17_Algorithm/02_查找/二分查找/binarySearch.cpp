
#include <iostream>
#include <ctime>
#include <cassert>
#include <sys/time.h>

template<typename T>
int binarySearch(T arr[], int n, T target)
{
    int l = 0, r = n - 1;
    
    while (l <= r) {    // [l...r]
        int mid = l + (r - l) / 2;
        if (arr[mid] == target) {
            return mid;
        }
        
        if (target > arr[mid])  // [mid + 1, r]
            l = mid + 1;
        else                    // [l, mid - 1]
            r = mid - 1;
    }
    
    return -1;
}

int *generateOrderedArray(int n)
{
    int * arr = new int[n];
    
    for (int i = 0; i < n; i++)
        arr[i] = i;
    
    return arr;
}

int main()
{
    int n = 1000000;
    int * data = generateOrderedArray(n);
    
    struct timeval b, e;
    int i;
    
    gettimeofday(&b, 0);
    
    for (i = 0; i < n; i++) {
        assert(i == binarySearch(data, n, i));
    }
    gettimeofday(&e, 0);
    
    std::cout << "binarySearch test complete." << std::endl;
    std::cout << "Time cost: " << double(e.tv_sec * 1000 + e.tv_usec / 1000 - b.tv_sec * 1000 - b.tv_usec / 1000) << std::endl;
    
    return 0;
}