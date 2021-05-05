
#include <stdio.h>

int main()
{
    int a[] = { 56, 22, 67, 32, 59, 12, 89, 26, 48, 37 };
    
    int i, j, low, high, mid;
    
    int ele;
    for (i = 1; i < sizeof(a) / sizeof(a[0]); i++) {
        j = i - 1;
        ele = a[i];
        low = 0, high = j;
        while (low <= high) {
            mid = low + (high - low) / 2;
            if (ele > a[mid])
                low = mid + 1;
            else
                high = mid - 1;
        }
        
        // printf("low=%d, high=%d, mid=%d\n", low, high, mid);
        
        for (j = i; j >= low; j--) {
            a[j] = a[j - 1];
        }
        a[low] = ele;
    }
    
    for (i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    return 0;
}