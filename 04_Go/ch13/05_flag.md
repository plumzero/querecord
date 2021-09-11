
`flag` 包是 Go 语言标准库提供的用来解析命令行参数的包，使得开发命令行工具更为简单。

flag 包支持的标志格式有:
* `-flag`: 代表 bool 值，相当于 -flag=true
* `-flag=x`: 支持所有的值
* `-flag x`: 不支持 bool 值标志

命令行参数(或参数)是指运行程序提供的参数，非 flag 命令行参数(或保留的命令行参数)可以简单理解为 flag 包不能解析的参数。

flag 包实现命令行参数的解析，大致需要以下几个步骤。

### flag 参数定义或绑定

定义 flags 有两种方式:
1. flag.Xxx()，其中 Xxx 可以是 Int、String 等，返回一个相应类型的指针，如:
```go
    var ip = flag.Int("flagname", 1234, "help message for flagname")
```

2. flag.XxxVar()，将 flag 绑定到一个变量上，如:
```go
    var flagvar int
    flag.IntVar(&flagvar, "flagname", 1234, "help message for flagname")
```

### flag 参数解析

在所有的 flag 定义完成之后，可以通过调用 `flag.Parse()` 进行解析。

flag 解析遇到 non-flag 参数就停止了。所以如果将 non-flag 参数放在最前面，flag 什么也不会解析。


### 分支程序

根据参数值，代码进入分支程序，执行相关功能。如下面的代码就提供了 -h 参数的功能:
```go
    if h || H {
        flag.Usage()
    }
```

[示例](05/flag_parse.go)
