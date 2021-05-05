
#include <stdio.h>

int partition(int a[], int low, int high)
{
    int pivot;
    
    pivot = a[low];
    
    while (low < high) {
        while (low < high && a[high] >= pivot)
            high--;
        if (low < high) {
            a[low] = a[high];
            low++;
        }
        while (low < high && a[low] <= pivot)
            low++;
        if (low < high) {
            a[high] = a[low];
            high--;
        }
        a[low] = pivot;
    }
    
    return low;
}

void quickSort(int a[], int low, int high)
{
    int pivot;
    if (low < high) {
        pivot = partition(a, low, high);
        quickSort(a, low, pivot - 1);
        quickSort(a, pivot + 1, high);
    }
}

int main()
{
    int a[] = { 56, 22, 67, 32, 59, 12, 89, 26, 48, 37 };
    
    int i;
    
    quickSort(a, 0, sizeof(a) / sizeof(a[0]) - 1);
    
    for (i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    return 0;
}