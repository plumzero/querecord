
### 渲染 HTML 模板

Gin 默认使用 Go 语言内置的 html/template 包处理 HTML 模板。


### 处理静态文件

一般网站开发中，会考虑把 js, css 文件以及资源图片放在一起，作为静态站点部署在 CDN，提升响应速度。静态资源可以通过如下方式加载:
```go
    func (group *RouterGroup) Static(relativePath, root string) IRoutes
    func (group *RouterGroup) StaticFile(relativePath, filepath string) IRoutes
    func (group *RouterGroup) StaticFS(relativePath string, fs http.FileSystem) IRoutes
```
* `StaticFile`: 用于加载单个文件。
* `StaticFS`: 用于加载一个完整的目录资源。

示例:
```go
    func main() {
        router := gin.Default()

        router.Static("/assets", "/var/www/gin/assets")
        router.Static("/favicon.ico", "./static/favicon.ico")
        router.Static("/static", "/var/www")

        router.StaticFile("/favicon.ico", "./resources/favicon.ico")
        router.StaticFS("/public", http.Dir("/website/static"))


        router.Run(":8080")
    }
```

不要想着用 Static/StaticFile/StaticFS 中的任何一个就可以一统江湖，要根据场合进行选择。
