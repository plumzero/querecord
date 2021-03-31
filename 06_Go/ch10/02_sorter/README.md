此示例为一个排序算法的比较程序，从命令行指定输入的数据文件和输出的数据文件，并指定对应的排序算法。

该程序的用法如下所示:
```go
    USAGE: sorter -i <in> -o <out> -a <qsort|bubblesort>
```
具体的执行过程如下:
```go
    $ ./sorter -I in.dat -o out.dat -a qsort
```

工程目录组织形式如下:
```sh
    sorter
    ├── bin
    │   └── unsorted.dat
    ├── pkg
    └── src
        ├── algorithms
        │   ├── bubblesort
        │   │   ├── bubblesort.go
        │   │   └── bubblesort_test.go
        │   └── qsort
        │       ├── qsort.go
        │       └── qsort_test.go
        └── sorter
            └── sorter.go
```
其中 `sorter.go` 是主程序，`qsort.go` 用于实现快速排序，`bubblesort.go` 用于实现冒泡排序。

设置 GOPATH 路径，并构建工程
```shell
    export GOPATH=$GOPATH:/path/to/sorter
    cd /path/to/sorter/bin
    go build sorter
```

运行及测试
```shell
    $ ./sorter -i unsorted.dat -o sorted.dat -a qsort
    infile = unsorted.dat outfile = sorted.dat algorithm = qsort
    The sorting process costs 2.781µs to complete.
    $ ./sorter -i unsorted.dat -o sorted.dat -a bubblesort
    infile = unsorted.dat outfile = sorted.dat algorithm = bubblesort
    The sorting process costs 3.191µs to complete.
    
    $ go test algorithms/bubblesort
    ok      algorithms/bubblesort   0.010s
    $ go test algorithms/qsort
    ok      algorithms/qsort        0.012s
```

生成静态库
```shell
    go install algorithms/qsort
    go install algorithms/bubblesort
```
执行上述命令后在 pkg 目录下有生成 qsort.a 和 bubblesort.a 文件。
