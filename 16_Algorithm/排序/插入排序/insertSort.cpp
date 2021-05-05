
#include <stdio.h>

int main()
{
    int a[] = { 56, 22, 67, 32, 59, 12, 89, 26, 48, 37 };
    
    int i, j;
    
    int ele;
    for (i = 1; i < sizeof(a) / sizeof(a[0]); i++) {
        j = i - 1;
        ele = a[i];
        while (j >= 0 && a[j] > ele) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = ele;
    }

    for (i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}