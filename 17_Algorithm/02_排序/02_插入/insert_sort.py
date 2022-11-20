#!/usr/bin/env python3

def insert_sort(a):
    size = len(a)
    i = 1
    while i < size:
        j = i - 1
        ele = a[i]
        while j >= 0 and a[j] > ele:
            a[j+1] = a[j]
            j -= 1
        a[j+1] = ele
        i += 1
        
    print(a)

def insert_sort_desc(a):
    size = len(a)
    i = 1
    while i < size:
        j = i - 1
        ele = a[i]
        while j >= 0 and a[j] < ele:
            a[j+1] = a[j]
            j -= 1
        a[j+1] = ele
        i += 1
        
    print(a)

a = [3, 1, 4, 1, 5, 9, 2, 6]
insert_sort(a)

insert_sort_desc(a)