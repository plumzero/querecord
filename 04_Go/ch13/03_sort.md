
sort 包中实现了几种基本的排序算法: 插入排序、快速排序和堆排序，但在使用 sort 包进行排序时无需具体考虑使用哪种排序方式:
```go
    func insertionSort(data Interface, a, b, int)
    func heapSort(data Interface, a, b int)
    func quickSort(data Interface, a, b, maxDepth int)
```

`sort.Interface` 接口定义了三个方法，如下:
```go
    type Interface interface {
        Len() int           // Len 为集合内元素的总数
        Less(i, j int) bool // 如果 index 为 i 的元素小于 index 为 j 的元素，则返回 true，否则返回 false
        Swap(i, j int)      // 交换索引为 i 和 j 的元素
    }
```
只要实现了这三个方法，就可以对数据集合进行排序。

sort 包原生支持 `[]int`、`[]float64`、`[]string` 三种内建数据类型切片的排序操作，即不必实现上面接口中的三个方法。

[对切片的排序](03/sort_slice.go)

### 自定义 sort.Interface 排序

如果是 []int、[]float64 和 []string 之外的某个具体结构体的排序，就需要自己实现 `sort.Interface` 了。

数据集合排序需要实现 sort.Interface 接口的三个方法，即: Len()、Swap(i, j int)、Less(i, j int)。实现这三个方法后，即可调用该包的 Sort() 方法进行排序。

[自定义数据集合的排序](03/sort_defined.go)

[自定义数据集合的排序二](03/sort_defined_2.go)


### sort.Slice 排序

为每种类型提供一个特定的 sort.Interface 的实现很烦琐。可以利用 sort.Slice 函数，把 Less(i, j int) 作为一个比较回调函数，传递给 `sort.Slice` 进行排序。

这种方法虽然方便，但一般不建议使用，因为在 sort.Slice 中使用了 reflect 。

[示例](03/sort_simple.go)
