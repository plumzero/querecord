
goroutine 是 Go 语言中的轻量级线程实现，则 Go 运行时(runtime)管理。

Go 通过 `go` 关键字实现一个 goroutine 并发执行实例:
```go
    func Add(x, y int) {
        z := x + y
        fmt.Println(z)
    }

    go Add(1, 1)
```
需要注意的是，如果 Add 函数有返回值，那么个这个返回值会被丢弃。

启动 goroutine 实例后，如果启动函数(通常在main函数中启动)在 goroutine 例程之前返回，此时可能就无法得到我们想要的结果。

我们可以采用类似于 C/C++ 中的做法进行例程间的协调同步。

[同步示例](t/02_goroutine_sync.go)。

事实上，Go 语言提供的 channel 消息通信机制可以优雅地实现协程之间的步调一致。
