
channel 是 Go 语言在语言级别提供的 goroutine 间的通信方式。因此可以使用 channel 在两个或多个 goroutine 之间传递消息。

channel 是类型相关的。也就是说，一个 channel 只能传递一种类型的值，这个类型需要在声明 channel 时指定。可以将 channel 认为是一种类型安全的管道。

### 基本语法

一般 channel 的声明形式为:
```go
    var chanName chan ElementType
```
ElementType 指定这个 channel 所能传递的元素类型。

可以直接使用内置函数 make() 定义一个 chan:
```go
    ch := make(chan int)
```

在 channel 的用法中，最常见的包括写入和读出。将一个数据写入(发送)至 channel 的语法为:
```go
    ch <- value
```
向 channel 写入数据通常会导致阻塞，直到有其他 goroutine 从这个 channel 中读取数据。

从 channel 中读取数据的语法是:
```go
    value := <-ch
```
如果 channel 之前没有写入数据，那么从 channel 中读取数据也会导致阻塞，直到 channel 中被写入数据为止。

通过读写阻塞，channel 实现了类似锁的功能，进而可以保证所有 goroutine 完成后主函数才返回。

[传递int类型测试](t/03_channel_int.go)

[传递map类型测试](t/03_channel_map.go)

[传递struct类型测试](t/03_channel_struct.go)

[channel地址打印测试](t/03_channel_addr.go)


### select

Go 语言在语言级别支持 `select` 关键字，用于处理异步 IO 问题。

select 用法与 switch 类似，不过有许多限制，其中最大的一条限制就是每个 case 语句里必须是一个 IO 操作，大致结构如下:
```go
    select {
        case <-chan1:
            // 如果 chan1 成功读到数据，则进行该 case 处理语句
        case chan2 <- 1:
            // 如果成功向 chan2 写入数据(1)，则进行该 case 处理语句
        default:
            // 如果上面都没有成功，则进入 default 处理流程
    }
```

[随机向channel写入数据测试](t/03_select.go)


### 缓冲机制

对于需要持续传输大量数据的场景，有必要为 channel 带上缓冲，从而达到消息队列的效果。

要创建一个带缓冲的 channel，在调用 make() 时将缓冲区大小作为第二个参数传入即可:
```go
    c := make(chan int, 1024)
```

从带缓冲的 channel 中读取数据可以使用与常规非缓冲 channel 完全一致的方法，也可以使用 `range` 关键字来实现更简便的循环读取:
```go
    for i := range c {
        fmt.Println("Received:", i)
    }
```

[示例程序](t/03_channel_int.go)


### 超时机制

在并发编程的通信过程中，最需要处理的就是超时问题，即向 channel 写数据时发现 channel 已满，或者从 channel 试图读取数据时发现 channel 为空。如果不正确处理这些情况，很可能导致整个 goroutine 锁死。

Go 语言没有提供直接的超时处理机制，但可以利用 select 方便地解决超时问题。因为 select 的特点是只要其中一个 case 已经完成，程序就会继续往下执行，而不会考虑其他 case 的情况。

[超时处理示例程序](t/03_timeout.go)


### channel 的传递

Go 语言中的 channel 本身也是一个原生类型，在定义后也可以通过 channel 来传递。

[程序示例](t/03_pass_channel.go)


### 单向 channel

channel 本身必然是同时支持读写的，所谓的单向 channel 概念，其实只是对 channel 的一种使用限制，即单向 channel 只能用于发送或者接收数据。

单向 channel 变量的声明如下:
```go
    var ch1 chan int        // 正常 channel
    var ch2 chan<- float64  // 只用于写入 float64 的单向 channel
    var ch3 <-chan int      // 只用于读取 int 的单向 channel
```

channel 支持单向 channel 和双向 channel 之间的类型转换，示例如下:
```go
    ch4 := make(chan int)
    ch5 := <-chan int(ch4)      // ch5 之后是一个单向的读取 channel
    ch6 := chan<- int(ch4)      // ch6 之后是一个单向的写入 channel
```

在将一个 channel 变量传递到一个函数时，可以通过将其指定为单向 channel 变量，从而限制该函数中可以对此 channel 的操作。

[单向channel的使用示例](t/03_one_way.go)

注意，单向 channel 不能转为双向 channel 。


### 关闭 channel

可以使用 Go 语言内置函数 close() 关闭 channel。

关闭 channel 很有必要。发送者发送完毕数据之后，接收者此时有必要了解到这种情况以停止不必要的等待。

一个 channel 被关闭后，再向该 channel 发送数据将导致 panic 异常。

当接收者从一个已经被关闭的 channel 读取完数据之后，后续的读取操作将不再阻塞，而是返回一个零值。可以利用这个特性来判断是否发送者已将 channel 关闭。
```go
    x, ok := <-ch
```
ok 是一个 bool 值，当其为 false 时表示 ch 已经被关闭。

[关闭channel示例](t/03_close.go)

另外，使用 range 也可以在 channel 关闭的时候自动跳出。

[channel关闭时，接收者通过range跳出示例](t/03_close_range.go)
