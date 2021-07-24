
package main

import (
    "net/http"
    "github.com/gin-gonic/gin"
)

// 浏览器中输入 IP:8080/user/login
func goLogin(c *gin.Context) {
    name := c.PostForm("name")
    password := c.PostForm("password")

    c.String(http.StatusOK, "username=%s,password=%s", name, password)
}

func main() {
    router := gin.Default()
    router.LoadHTMLGlob("./*")		// 加载当前路径下的所有 html

    router.GET("/user/login", func(c *gin.Context) {
        c.HTML(http.StatusOK, "01_handlerfunc.html", nil)
    })

    router.POST("/user/login", goLogin)

    router.Run(":8080")
}