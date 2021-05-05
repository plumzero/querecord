
Go 内置的 net/http 包提供了最简洁的 HTTP 客户端实现，可以无需借助第三方网络通信库(如libcurl)就可以直接使用 HTTP 中用得最多的 GET 和 POST 方式请求数据。

net/http 包的 Clinet 类型提供了如下几个方法，可以用最简洁的方式实现 HTTP 请求。

### http.Get()

```go
    func (c * Client) Get(url string) (r * Response, err error)
```

示例: 请求一个网站首页，将其网页内容打印到标准输出流中。
```go
    resp, err := http.Get("http://example.com/")
    if err != nil {
        // deal with error ...
        return
    }
    defer resp.Body.close()
    io.Copy(os.Stdout, resp.Body)
```


### http.Post()

```go
    func (c * Client) Post(url string, bodyType string, body io.Reader) (r * Response, err error)
```
传递的 3 个参数依次表示为: 请求的目标 URL，将要 POST 数据的资源类型(MIMEType)以及数据的比特流([]byte形式)。

示例: 上传一张图片。
```go
    resp, err := http.Post("http://example.com/upload", "image/jpeg", &imageDataBuf)
    if err != nil {
        // deal with error ...
        return
    }
    if resp.StatusCode != http.StatusOK {
        // deal with http error ...
        return
    }
    // ...
```


### http.PostForm()

```go
    func (c * Client) PostForm(url string, data url.Values) (r * Response, err error)
```
http.PostForm() 方法实现了标准编码格式为 `application/x-www-form-urlencoded` 的表单提交。

示例: 模拟 HTML 表单提交一篇文章。
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


### http.Head()

```go
    func (c * Client) Head(url string) (r * Response, err error)
```
该方法只会请求目标 URL 的头部信息，即请求成功时 HTTP 响应只返回 HTTP Header 而不返回 HTTP Body 。

示例: 请求一个网站首页的 HTTP Header 信息:
```go
    resp, err := http.Head("http://example.com/")
```


### http.Do()

多数情况下，http.Get() 和 http.PostForm() 就可以满足需求，但是如果客户端发起的 HTTP 请求需要更多的定制信息，此时就需要设定一些自定义的 HTTP Header 字段。比如: 设定自定义的 "User-Agent" 或者传递 Cookie 等。

此时可以使用 net/http 包 http.Client 对象的 Do() 方法实现:
```go
    func (c * Client) Do(req * Request) (resp * Response, err error)
```

示例:
```go
    req, err := http.NewRequest("GET", "http://example.com", nil)
    // ...
    req.Header.Add("User-Agent", "GoBook Custom User-Agent")
    // ...
    client := &http.Client{ /***/ }
    resp, err := client.Do(req)
    // ...
```
