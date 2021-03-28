
## 说明
- 从 Go 1 开始，Go 引入了命令行工具进行工程管理。
- Go 命令行工具消除了 C/C++ 中工程文件的概念，完全采用目录结构和包名来推导工程结构和构建顺
  序。
  
## calcproj 工程示例
- 此示例工程被分割为两个部分:
    + 可执行程序，名为 calc；
    + 算法库，名为 simplemath，每个 command 对应于一个同名的 go 文件，比如 add.go。
- 工程目录组织形式如下:
    <calcproj>
    |--<src>
        |--<calc>
            |--calc.go
        |--<simplemath>
            |--add.go
            |--add_test.go
            |--sqrt.go
            |--sqrt_test.go
    |--<bin>
    |--<pkg> # 包将被安装到此处
  在上面的结构里，带尖括号的名字表示其为目录。 xxx_test.go 表示的是一个对于  xxx.go 的单元测
  试，这也是 Go 工程里的命名规则。
- 为了能够构建这个工程，需要先把这个工程的根目录加入到环境变量 GOPATH 中。假设 calcproj 目录
  位于 ~go/ 目录下，则可以进行如下设置:
  ```shell
    export GOPATH=~go/calcproj
  ```  
- 开始构建工程。如果我们希望把生成的可执行文件放到 calcproj/bin 目录下，需要进入 bin 目录下执
  行如下命令:
  ```shell
  $ pwd
  /home/go/calcproj/bin
  $ go build calc
  ```
  顺利的话，将在该目录下生成一个名称为 calc 的可执行文件。可以执行如下类似命令，输出结果如下:
  ```shell
    $ ./calc 
    USAGE: calc command [arguments] ...

    The commands are:
            add     Addition of two values.
            sqrt    Square root of a non-negative value.
    $ ./calc add 2 3
    Result:  5
    $ ./calc sqrt 9
    Result:  3
  ```
- 在写 simplemath 包时，为每一个关键的函数编写了对应的单元测试代码，分别位于 add_test.go 和 
  sqrt_test.go 中。且之前设置了 GOPATH，所以可以在任意目录下执行以下命令进行这些单元测试:
  ```shell
    $ go test simplemath
    ok      simplemath      0.007s
  ```
  可以看到，运行结果列出了测试结果、测试内容和测试时间。
  
## sorterproj 工程示例
- 此示例为一个排序算法的比较程序，从命令行指定输入的数据文件和输出的数据文件，并指定对应的排序算法。
  该程序的用法如下所示:
  ```go
    USAGE: sorter -i <in> -o <out> -a <qsort|bubblesort>
  ```
  具体的执行过程如下:
  ```go
    $ ./sorter -I in.dat -o out.dat -a qsort
  ```
- 工程目录组织形式如下:
    <sorterproj>
        |--<src>
            |--<sorter>
                |--sorter.go
            |--<algorithms>
                |--<qsort>
                    |--qsort.go
                    |--qsort_test.go
                |--<bubblesort>
                    |--bubblesort.go
                    |--bubblesort_test.go
        |--<pkg>
        |--<bin>
  其中 sorter.go 是主程序，qsort.go 用于实现快速排序，bubblesort.go 用于实现冒泡排序。
- 设置 GOPATH 路径，并构建工程
  ```shell
    export GOPATH=~go/sorterproj
    $ echo $GOPATH
    /home/go/sorterproj
    $ pwd
    /home/go/sorterproj/bin
  ```
  进入 bin 目录下，构建工程
  ```shell
    $ pwd
    /home/go/sorterproj/bin
    $ go build sorter
  ```
  生成可执行文件
  ```shell
    go build sorter
  ```
  只要设置好 GOPATH 路径，可以在任意目录下生成可执行文件 sorter
- 运行及测试
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
- 生成静态库
  ```shell
    go install algorithms/qsort
    go install algorithms/bubblesort
  ```
  执行上述命令后在 pkg 目录下有生成 qsort.a 和 bubblesort.a 文件。
  如果是在任意目录下直接执行如下命令，而不是 go build sorter 命令，则只会在 bin 目录下生成可执行文件。
  ```shell
    go install sorter
  ```