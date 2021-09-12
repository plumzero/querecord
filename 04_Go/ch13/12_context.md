
在 Go 语言中，每个独立调用一般都会被单独的协程处理。但在处理一个请求时，往往可能需要在多个协程之间进行信息传递，甚至包括一层层地递进顺序传递，而且这种信息往往具有一定的场景状态。如一个请求可能往生出各个协程之间需要满足一定的约束关系，如登录状态、前一个协程的计算结果、传递请求全局变量等功能。

Go 提供了 context 包，可以在多个协程之间传递请求相关的数据、主动取消上下文或按照时间自动取消上下文等。

每个协程在执行之前，一般都需要了解当前的执行状态，通常会将这些状态包装在上下文变量中进行传递。

当程序接收到一个网络请求 Request，在处理 Request 时，可能需要开启不同的协程来获取数据与逻辑处理，即一个请求 Request 可能需要在多个协程中被处理。这些协程需要共享 Request 的一些信息，同时当顶层 Context 被取消或者超时的时候，所有从这个顶层 Request 创建的 Context 也应该结束。Context 就像是 Request 中的全局变量能让大家共享数据，当然实际上它是需要创建并传递的。

context 包实现了在程序协程之间共享状态变量的方法，在被调用程序单元的外部，通过设置上下文变量 ctx，将过期或取消信号传递给被调用的程序单元。

`context.Context` 包含过期、取消信号、request值传递等，方法在多个协程中线程安全。其结构如下: 
```go
    type Context interface {
        // Done 方法在 context 被取消或者超时返回一个 close 的 channel
        Done() <- chan struct{}

        Err() error

        // Deadline 返回 context 超时时间
        Deadline() (deadline time.Time, ok bool)

        // Value 返回 context 相关 key 对应的值
        Value(key interface{}) interface{}
    }
```
* `Deadline`: 返回一个超时时间，超时后 Context 无效。
* `Done`: 返回一个通道，当 Context 被取消或过期时，该通道关闭，即它是一个表示是否已关闭的信号。
* `Err`: 当 Done 通道关闭后，Err 方法表明 Context 被取消的原因。
* `Value`: 可以共享的数据。

Context 的创建和调用关系总是层层递进的，Context 的创建者的协程可以主动关闭其下层的 Context 的执行。它们之前的关系组织，就像一棵上下文树。

要创建上下文树，首先要得到根节点，`context.Background` 函数的返回值就是根节点:
```go
    func Background() Context
```
这个函数会返回一个空的上下文，该上下文一般由接收请求的第一个协程创建，并作为根节点，它不能被取消，没有值，也没有过期时间。它常常作为处理 Request 的顶层上下文存在。

context 包提供了以下四种函数来创建子孙节点:
```go
    func WithCancel(parent Context) (ctx Context, cancel CancelFunc)
    func WithDeadline(parent Context, deadline time.Time) (Context, CancelFunc)
    func WithTimeout(parent Context, timeout time.Duration) (Context, CancelFunc)
    func WithValue(parent Context, key interface{}, val interface{}) Context
```
这些函数都接收一个 Context 类型的参数 parent，并返回一个 Context 类型的值，这样就层层创建出不同的节点。

使用 Context 的协程是无法取消某个操作的，只有父协程可以取消操作。在父协程中可以通过 `WithCancel` 函数获得一个 `CancelFunc` 函数类型变量，从而手工取消这个 Context 。

WithCancel 函数将父节点 Context 复制到子节点，并且返回一个额外的 CancelFunc 函数类型变量，该函数类型的定义为:
```go
    type CancelFunc func()
```
调用 CancelFunc 对象 cancel 将取消对应的 Context 对象，这就是主动取消 Context 的方法。

这样，在父节点的 Context 所对应的环境中，通过 WithCancel 函数在创建该节点的 Context 的同时，也获得了该节点 Context 的控制权，即一旦执行 cancel 函数，该节点 Context 也就结束了。而子节点则需要根据 `context.Done()` 来判断是否结束，例如:
```go
    select {
        case <-ctx.Done()
    }
```

`WithDeadline` 函数的作用也差不多，它返回的 Context 类型值同样是 parent 的副本，但其过期时间由 deadline 和 parent 的过期时间共同决定。这是因为父节点过期时，其所有的子孙节点必须同时关闭；反之，返回的父节点的过期时间则为 deadline 。

`WithTimeout` 函数与 WithDeadline 类似，不过它传入的是上下文从现在开始剩余的生命时长。

当顶层的 Request 请求函数结束后，就可以取消某个上下文，从而再在对应协程中根据 `ctx.Done()` 来决定是否结束协程本身。

`WithValue` 函数返回 parent 的一个副本，调用该副本的 `Value(key)` 方法将得到对应 key 的值。不止可以将根节点原有的值保留，还可以在子孙节点中加入新的值，注意若存在新旧 Key 相同的情况，则旧 Key 的值会被覆盖。

Context 对象的生存周期一般仅为一个请求的处理周期，即针对一个请求创建一个 Context 变量(它是上下文树的根)。在请求处理结束后，撤销此变量，释放资源。

使用上下文时需遵循以下规则:
* 上下文变量需要作为第一个参数使用，一般命名为 ctx 。
* 不要传入一个 nil 的上下文，不确定 Context 时可传一个 context.TODO 。
* 使用上下文的 Value 相关方法只传递请求相关的元数据，不要传递可选参数。
* 同样的上下文可以用来传递到不同的协程中，上下文在多个协程中是安全的。

在子上下文被传递到的协程中，应该对该子上下文中的 Done 通道进行监控，一旦该通道被关闭(即上层运行环境撤销了本协程的执行)，应主动终止对当前请求信息的处理，释放资源并返回。

[通过上下文控制子协程的运行](12/parent_cancel_control.go)

[嵌套上下文运行状态](12/child_monitor_control.go)


