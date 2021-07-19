
Go 内置的 net/http 包提供了一个被称为 Client 的结构体，可以无需借助第三方网络通信库(如libcurl)就可以直接使用 HTTP 中用得最多的 GET 和 POST 方式请求数据。

net/http 包中提供了一个默认的 Client 类型的变量可直接使用:
```go
    var DefaultClient = &Client{}
```

Client 结构体实现了 Get()、Post() 两个请求函数，其定义如下:
```go
    func Get(ur string) (resp *Response, err error)
    func Post(url, contentType string, body io.Reader) (resp *Response, err error)
```

其中 Get() 函数实现如下:
```go
    func Get(url string) (resp *Response, err error) {
        return DefaultClient.Get(url)
    }
```
在上面的 Get() 函数中，使用了 DefaultClient 对象的 Get() 方法。该 Get() 方法的具体实现如下:
```go
    func (c *Client) Get(url string) (resp *Response, err error) {
        req, err := NewRequest("GET", url, nil) 
        if err != nil {
            return nil, err
        }
        return c.Do(req)
    }
```

同样，net/http 包的 Post() 函数的具体实现代码如下:
```go
    func Post(url, contentType string, body io.Reader) (resp *Response, err error) {
        return DefaultClient.Post(url, contentType, body)
    }
```
Post() 函数则使用了 DefaultClient 对象的 Post() 方法，具体实现如下:
```go
    func (c *Client) Post(url, contentType string, body io.Reader) (resp *Response, err error) {
        req, err := NewRequest("POST", url, body)
        if err != nil {
            return nil, err
        }
        req.Header.Set("Content-Type", contentType)
        return c.Do(req)
    }
```

Client 结构体的 Get() 和 Post() 函数直接使用了 `NewRequest()` 函数。它是一个通用函数，定义如下:
```go
    func NewRequest(method, url string, body io.Reader) (*Request, error)
```
第 1 个参数为请求类型，可以是 "GET" "POST" "PUT" "DELETE" 等。第 2 个参数为请求地址。如果 body 参数实现了 io.Closer 接口，则 Request 返回值的 Body 字段会被设置为 body 参数的值，并会被 Client 结构体的 Do()、Post() 和 PostForm() 方法关闭。

在 Go 语言中创建客户端，最核心的 HTTP 请求方法是 NewRequest() 函数。因为 PUT、DELETE 方法在 Go 语言中没有被单独封装，所以只能通过直接调用 NewRequest() 函数来实现。

[创建GET请求示例](t/02_Get.go)

[创建POST请求示例，只作示例，无法运行](t/02_Post.go)


此外，net/http 的 Client 还提供了 `PostForm()` 方法用于标准编码格式为 `application/x-www-form-urlencoded` 表单的提交，示例如下:
```go
    resp, err := http.PostForm("http://example.com/posts",
                                url.Values{"title" : {"article title"},
                                           "content": {"article body"}})
    if err != nil {
        // deal with error ...
        return
    }
    ...
```

如果客户端发起的 HTTP 请求需要更多的定制信息，此时就需要设定一些自定义的 HTTP Header 字段。比如: 设定自定义的 "User-Agent" 或者传递 Cookie 等。此时可以使用 net/http 包 http.Client 对象的 `Do()` 方法实现:
```go
    func (c * Client) Do(req * Request) (resp * Response, err error)
```

[创建PUT请求示例，只作示例，无法运行](t/02_Put.go)

[创建DELETE请求示例，只作示例，无法运行](t/02_Delete.go)

net/http 包提供了 Header 类型，用于请求头信息的获取和填充，其定义如下:
```go
    type Header map[string][]string
```
用户可以通过 http.Header 对象定义自己的 Header:
```go
    headers := http.Header{ "token": {"dh033fjdlshdlf3032df"} }
    headers.Add("Accept-Charset", "UTF-8")
    headers.Set("Host", "for-test")
    headers.Set("Location", "www.example.com")
```
