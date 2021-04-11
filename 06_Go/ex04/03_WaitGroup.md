
### WaitGroup

等待一簇 goroutine 的结束。main goroutine 调用 Add() 方法设置要等待的 goroutine 计数，之后每个 groutine 执行之后调用 Done() 方法将计数减 1，同时 Wait() 方法阻塞等待所有 goroutine 结束返回。

```go
    func (wg * WaitGroup) Add(delta int)
    func (wg * WaitGroup) Done()
    func (wg * WaitGroup) Wait()
```

[程序示例](03/WaitGroup.go)
