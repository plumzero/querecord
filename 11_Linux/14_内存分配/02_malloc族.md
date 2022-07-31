
### malloc

一般情况下，C 程序使用 malloc 函数族在堆上分配和释放内存。通过该函数可以允许随意释放内存块，它们被维护于一张空闲内存列表中，在后续内存分配调用时循环使用。
```c
    #include <stdlib.h>

    void *malloc(size_t size);
```
若无法分配内存(或许是因为已经抵达 progjam break 所能达到的地址上限)，则 malloc() 返回 NULL，并设置 errno 以返同错误信息。虽然分配内存失败的可能性很小，但所有对 malloc() 以及后续提及的相关函数的调用都应对返同值进行错误检查。


### free

free()函数释放 ptr 参数所指向的内存块，该参数可以是之前由 malloc() 返回指向的内存。
```c
    #include <stdlib.h>

    void free(void *ptr);
```

一般情况下，free 并不降低 program break 的位置，而是将这块内存填加到空闲内存列表中，供后续的 malloc() 函数循环使用。这么做是出于以下几个原因:
* 被释放的内存块通常会位于堆的中间，而非堆的顶部，因而降低 program break 是不可能的。
* 它最大限度地减少了程序必须执行的 sbrk() 调用次数。(系统调用的开销虽小，却也颇为可观。)
* 在大多数情况下，降低 program break 的位置不会对那些分配大量内存的程序有多少帮助，因为它们通常倾向于持有已分配内存或是反复释放和重新分配内存，而非释放所有内存后再持续运行一段时间。

但在某种情况下，free() 函数的 glibc 实现会在释放内存时将相邻的空闲内存块合并为一整块更大的内存(这样做是为了避免在空闲内存列表中包含大量的小块内存碎片，这些碎片会因空间太小而难以满足后续的内存分配请求)。具体能否实现要看堆顶空闲内存是否"足够"大，"足够"取决于 malloc 函数行为的控制参数(128KB 为典型值)，若符合 free() 函数的 glibc 实现会调用 sbrk() 来降低 program break 的地址。

当进程终止时，其占用的所有内存都会返还给操作系统，这包括在堆内存中由 malloc 函数包内一系列函数所分配的内存。基于内存的这一自动释放机制，对于那些分配了内存并在进程终止前持续使用的程序而言，通常会省略对 free 的调用。


### calloc 和 realloc

函数 calloc() 用于给一组相同对象分配内存:
```c
    #include <stdlib.h>

    void *calloc(size_t numitems, size_t size);
            Returns pointer to allocated memory on success, or NULL on error
```

realloc() 函数用来调整(通常是增加)一块内存的大小，而此块内存应是之前由 malloc 包中函数所分配的。
```c
    #include <stdlib.h>

    void *realloc(void *ptr, size_t size);
            Returns pointer to allocated memory on success, or NULL on error
```
