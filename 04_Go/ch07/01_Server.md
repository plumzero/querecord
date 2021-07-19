
要创建一个 Go 语言的 HTTP 服务器端，首选 需要使用 `HandleFunc()` 函数注册路由，然后通过 `ListenAndServe()` 函数开启对客户端的监听。

ListenAndServe() 函数有两个参数，分别是监听端口号和事件处理器 handler。在 Go 语言中，事件处理器 Handler 接口的定义如下:
```go
    type Handler interface {
        ServeHTTP(ResponseWriter, *Request)
    }
```
只需要实现了这个接口，就可以实现自己的 handler 处理器。Go 语言在 net/http 包中已经提供了实现这个接口的公共方法:
```go
    type HandlerFunc func(ResponseWriter, *Request)

    func (f HandlerFunc) ServeHTTP(w ResponseWriter, r *Request) {
        f(w, r)
    }
```

[简单服务器示例](t/01_hello.go)

