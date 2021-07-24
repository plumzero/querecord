
Gin 主要通过上下文对象提供的 `SetCookie()` 和 `Cookie()` 两个方法操作 cookie，这两个函数都是对 Go 语言 net/http 包中的 http.SetCookie() 方法的重新 封装而已。

依然有些问题待测试:
* 浏览器中是否对 cookie 进行了保存。客户端断开重连后，能否重新获取之前保存在浏览器中的 cookie ?
* 服务端对客户端发送过来的过期 cookie 的处理。


### 设置 cookie

Gin 使用 SetCookie() 方法设置 cookie，定义如下:
```go
    func (c *gin.Context) SetCookie(name, value string, maxAge int, path, domain string, secure, httpOnly bool)
```

使用示例如下:
```go
    router := gin.Default()
    router.GET("/cookie", func(c *gin.Context) {
        c.SetCookie("my_cookie", "cookie_value", 3600, "/", "localhost", false, true)
    })
```


### 读取 cookie

Gin 使用 Cookie() 方法读取 cookie。

使用示例如下:
```go
    func Handler(c *gin.Context) {
        data, err := c.Cookie("my_cookie")
        if err == nil {
            c.String(http.StatusOK, data)
            return
        }
        c.String(http.StatusNotFound)
    }
```


### 删除 cookie

通过将 SetCookie() 方法的 MaxAge 参数设置为 -1，可以达到删除 cookie 的目的。

使用示例如下:
```go
    func Handler(c *gin.Context) {
        c.SetCookie("my_cookie", "cookie_value", -1, "/", "localhost", false, true)
        c.String(http.StatusOK, "delete my_cookie success")
    }
```
