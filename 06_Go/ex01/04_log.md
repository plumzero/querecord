
Go 语言实现日志的功能主要依赖于 log 包，log 包中提供了 logger 类型用于对日志的操作。

New() 函数用于创建 logger 类型:
```go
    func New(out io.Writer, prefix string, flag int) *Logger
```
其中 out 是日志写入的目标; prefix 是日志内容的前缀; flag 表示日志的类型，这个在 log 包中的 const 常量中有定义:

|    flag 常量    | 含义 |
|:---------------|:--------|
| Ldate          | 日期: 2021/04/18 |
| Ltime          | 时间: 01:23:23 |
| Lmicroseconds  | 微秒级: 01:23:23.123123, Ltime 的补充 |
| Llongfile      | 文件全路径名+行号: /path/to/file.go:66 |
| Lshortfile     | 文件名+行号: file.go:66 |
| LUTC           | UTC 时间 |
| LstdFlags      | = Ldate | Ltime, 这是标准的 logger 初始值 |

log 包提供了三种方法用于将信息输出到 logger 对象中，分别是 `Print()`, `Fatal()` 以及 `Panic()` 。其中:
* Print() 表示将日志信息写到标准 logger 中
* Fatal() 表示在调用 Print() 后继续调用 os.Exit(1) 方法
* Panic() 表示在调用 print() 后调用 panic() 方法

log 包中还有一个 `Output()` 方法用于写入输出一次日志事件。其定义如下:
```go
    func (l *Logger) Output(calldepth int, s string) error
```

calldepth 用于控制日志堆栈输出深度，正常情况下堆栈深度为 2 层，所以其预定义的值为 2, s 是要打印的文本，如果末尾没有换行符会默认加上。

[使用Print和Fatal类型输出至logger示例](04/log_print_fatal.go)

[使用Panic类型输出logger示例](04/log_panic.go)

[错误处理与logger的结合示例](04/log_errors.go)
