
### 渲染 HTML 模板

Gin 默认使用 Go 语言内置的 html/template 包处理 HTML 模板。


### 处理静态文件

在 Gin 中，如果项目中包含 JS、CSS、JPG 之类的静态文件，可以通过如下方式访问:
```go
    func main() {
        router := gin.Default()
        router.Static("/assets", "/var/www/gin/assets")
        router.Static("/favicon.ico", "./static/favicon.ico")

        router.Run(":8080")
    }
```
