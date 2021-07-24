
session 和 Cookie 的主要目的是为了弥补 HTTP 的无状态特性。服务端可以利用 session 存储客户端在同一个会话期间的一些操作记录。

服务端在第一次接收到请求时，会开辟一块 session 空间(创建了 session 对象，存储结构为 ConcurrentHashMap)，同时生成一个 sessionid，并通过响应头的 `Set-Cookie: JSESSIONID=xxxxxxx` 的 cookie 信息，该 cookie 的过期时间一般为浏览器结束。

HTTP 协议中的 cookie 由服务端生成，发送给客户端，后者将其存储。接下来，在客户端每次向该服务器端发送请求时，请求头中都会有该 cookie 信息(包含 sessionid)，服务器从其中读取 JSESSIONID，获取 sessionid，确认是否为同一个请求。

cookie 无法跨域传递，也就是说一个 session 只对一条连接有效。

如果没有指定 `Expires` 或 `Max-Age` 指令，cookie 会在客户端关闭时删除。但是，Web 浏览器可能会使用会话还原，这会使得大多数会话 cookie 保持"永久"状态，就像从未关闭过浏览器。用户可以通过指定日期(`Expires`)或特定时间长度(`Max-Age`)使其到达时间后过期。

`Domain` 和 `Path` 标识定义了 cookie 的作用域，即 cookie 应该被发送给哪些 URL。Domain 标识指定了哪些主机可以接受 cookie，如果不指定 Domain 则默认为当前主机(不包含子域名)；如果指定了 Domain 则一般包含子域名。例如，如果设置 "Domain=baidu.com"，则 cookie 也包含在子域名中(如 news.baidu.com/)。如果设置 "Path=/test"，则以下地址都会匹配: "/test"、"/test/news/"、"/test/news/id"。


### Go 使用 cookie

Go 标准库的 net/http 包中定义了名为 `Cookie` 的结构体，结构体代表一个出现在 HTTP 响应头中的 Set-Cookie 的值，或者 HTTP 请求头中的 cookie 的值。定义如下:
```go
    type Cookie struct {
        Name        string
        Value       string
        Path        string
        Domain      string
        Expires     time.Time
        RawExpires  string
        MaxAge      int     // =0 表示未设置该属; <0 表示立即删除，相当于设置了 =0; >0 表示设置了该属性，单位为 s
        Secure      bool
        HttpOnly    bool
        Raw         string
        Unparsed    []string    // 未解析的 "属性-值" 对应的原始文本
    }
```

Go 语言通过 `SetCookie()` 函数设置 cookie，定义如下:
```go
    func SetCookie(w ResponseWriter, cookie *Cookie)
```

[设置cookie示例](t/03_SetCookie.go)

Request 对象一共有 3 个处理 cookie 的方法: 2 个获取 cookie 和 1 个添加 cookie 。

获取 cookie 的方法为:
```go
    func (r *Request) Cookies() []*Cookie
    func (r *Request) Cookie(name string) (*Cookie, error)
```
第一个用于返回所有的 cookie，第二个用于返回指定的 cookie。

向请求中添加一个 cookie 的方法为:
```go
    func (r *Request) AddCookie(c *Cookie)
```

[获取和添加cookie示例](t/03_Cookie_AddCookie.go)


### Go 使用 session

Go 标准库中并没有提供实现 session 的方法，这里提供一个设计思路。

1.定义一个名为 Session 的接口

Session 提供 4 种操作接口: 设置值、获取值、删除值和获取当前的 sessionid:
```go
    type Session interface {
        Set(key, value interface{}) error
        Get(key interface{}) interface{}
        Delete(key interface{}) error
        SessionID() string
    }
```

2.创建 session 管理器




