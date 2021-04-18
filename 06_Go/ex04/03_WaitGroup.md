
Go 语言中的同步是通过 sync.WaitGroup 来实现的。WaitGroup 实现了一个类似队列的结构，可以一直向队列中添加(Add)任务。当任务完成后便从队列中删除(Done)，如果队列中的任务没有完成，则可以通过 Wait() 来阻塞，防止程序继续进行，直到所有的队列任务都完成，程序终止。


WaitGroup 对外暴露了三个方法:
```go
    func (wg * WaitGroup) Add(delta int)
    func (wg * WaitGroup) Done()
    func (wg * WaitGroup) Wait()
```
* Add: 添加或者减少等待协程的数量
* Done: 相当于 Add(-1)
* Wait: 执行阻塞，直到所有的 WaitGroup 数量变为 0

[程序示例](03/WaitGroup.go)
