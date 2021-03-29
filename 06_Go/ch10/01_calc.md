
此示例实现了一个简单的计算器。

[calcproj工程项目代码目录](calcproj)

工程目录组织形式如下:
```sh
    calcproj
    ├── bin
    ├── pkg
    └── src
        ├── calc
        │   └── calc.go
        └── simplemath
            ├── add.go
            ├── add_test.go
            ├── sqrt.go
            └── sqrt_test.go
```
函数入口定义在 `calc.go` 中， simplemath 定义程序执行依赖的文件。bin 和 pkg 分别存放生成的可执行文件和包(的安装)。

`xxx_test.go` 表示的是一个对于 `xxx.go` 的单元测试，这也是 Go 工程里的命名规则。

为了能够构建这个工程，需要先把这个工程的根目录加入到环境变量 `GOPATH` 中。如下:
```shell
    export GOPATH=/path/to/calcproj
```

现在开始构建工程。只要设置好 GOPATH 路径，可以在任意目录下生成可执行文件 calc 。这里我们在 `calcproj/bin` 目录下生成可执行文件:
```shell
    $ pwd
    /path/to/calcproj/bin
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

> 单元测试

在写 simplemath 包时，我们为每一个关键的函数编写了对应的单元测试代码，分别位于 `add_test.go` 和 `sqrt_test.go` 中。且之前设置了 GOPATH，所以可以在任意目录下执行以下命令进行这些单元测试:
```shell
    $ go test simplemath
    ok      simplemath      0.007s
```
可以看到，运行结果列出了测试结果、测试内容和测试时间。
