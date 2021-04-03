
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

[发送int测试](t/03_channel_int.go)

[发送map测试](t/03_channel_map.go)

[发送struct测试](t/03_channel_struct.go)


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



