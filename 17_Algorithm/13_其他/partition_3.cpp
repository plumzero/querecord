
#include <stdio.h>

// 这种方法不用将分界元素添加到数组中
// 假设将小于分界元素的数组元素移到左边，将大于等于分界元素的数组元素移到右边

// 也是定义两个游标，不妨设为 i,j ，开始时两游标均指向数组首元素。
// 其实就是类似于快慢指针了啦。最终分成 [0, j) 和 [j, i] 两块元素 
void swap(int a[], int i, int j)
{
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

int partition(int a[], int len, int val)    // val 为分界元素
{
    int i, j;
    i = j = 0;

    for (i = 0; i < len; i++) {
        if (a[i] < val) {
            if (i != j)
                swap(a, i, j);
            j++;
        }
    }

    return j;
}

int main()
{
    int a[] = { 1, 2, 6, 7, 8, 3, 4, 5, 9 };
    int len = sizeof(a) / sizeof(int);
    int val = 6;

    int pi = partition(a, len, val);

    printf("pi=%d\n", pi);
    for (int i = 0; i < pi; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    for (int i = pi; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}