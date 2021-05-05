
#include <stdio.h>

int main()
{
    int a[] = { 56, 22, 67, 32, 59, 12, 89, 26, 48, 37 };
    
    int step = 5;   /** 作为起始增量 */
    
    int i, j;
    
    int ele;
    while (step) {
        for (i = step; i < sizeof(a) / sizeof(a[0]); i++) {
            if (a[i] < a[i - step]) {   /** 序列中某个元素无序，将 a[i] 插入到 a[.]...a[i-step] 序列中 */
                ele = a[i];
                for (j = i - step; j >= 0 && ele < a[j]; j -= step) {
                    a[j + step] = a[j];
                }
                a[j + step] = ele;
            }
        }
        
        step /= 2;
    }
    
    for (i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}