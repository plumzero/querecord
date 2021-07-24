
package main

import "github.com/gin-gonic/gin"

func main() {
    // 创建一个默认的路由引擎
    r := gin.Default()
    // GET: 请求方式  /hello: 请求的路径
    // 当客户端以 GET 方法请求 /hello 路径时，会执行后面的匿名函数
    r.GET("/hello", func(c *gin.Context) {
        c.JSON(200, gin.H{
            "message": "Hello World!",
        })
    })
    // 启动 HTTP 服务，默认在 0.0.0.0:8080 启动服务
    r.Run()
}