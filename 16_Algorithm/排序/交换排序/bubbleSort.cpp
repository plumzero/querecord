
#include <stdio.h>

int main()
{
    int a[] = { 56, 22, 67, 32, 59, 12, 89, 26, 48, 37 };
    
    int i, j;
    int flag = 1;
    
    int n = sizeof(a) / sizeof(a[0]);
    
    int ele;
    for (i = 1; i < n && flag; i++) {       /** 最多比较 n - 1 趟 */
        flag = 0;
        for (j = 0; j < n - i; j++) {
            if (a[j] > a[j + 1]) {
                ele = a[j];
                a[j] = a[j + 1];
                a[j + 1] = ele;
                flag = 1;
            }
        }
    }
    
    for (i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    return 0;
}