
除了可以利用 WaitGroup 实现同步协程之外，Cond 通过借助 lock 实现线程阻塞也可以实现类似的效果。

Cond 只定义了三个方法: Wait(), Signal(), Broadcast() 。

Signal() 函数负责通知已经获取锁的协程解除阻塞状态开始正常运行。但是 Signal() 只能通知随机一个获取到锁的协程，可以使用 Broadcast() 方法来通知所有的协程全部解除阻塞状态。

[程序示例](03/cond_signal.go)
