
#include <stdio.h>

int main()
{
    int a[] = { 56, 22, 67, 32, 59, 12, 89, 26, 48, 37 };
    
    int i, j, k;
    
    int n = sizeof(a) / sizeof(a[0]);
    
    int ele;
    for (i = 0; i < n - 1; i++) {   /** 最后一个元素是不需要比较的，因为它就是遗留下的最大的。 */
        j = i;
        for (k = i + 1; k < n; k++) {
            if (a[k] < a[j])
                j = k;
        }
        if (j != i) {
            ele = a[i];
            a[i] = a[j];
            a[j] = ele;
        }
    }

    for (i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}