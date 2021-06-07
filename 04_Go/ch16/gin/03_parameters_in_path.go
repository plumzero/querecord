package main

import (
    "net/http"
    "github.com/gin-gonic/gin"
)

// curl http://127.0.0.1:8080/user/...

func main() {
    router := gin.Default()

    // 必选路由
    // √	/user/john
    // × 	/user/
    // ×    /user
    router.GET("/user/:name", func(c *gin.Context) {
        name := c.Param("name")
        c.String(http.StatusOK, "Hello %s", name)
    })

    // 可选路由
    // √	/user/john/
    // √	/user/john/send
    // √	/user/john          redirect to /user/john/ if not match
    router.GET("/user/:name/*action", func(c *gin.Context) {
        name := c.Param("name")
        action := c.Param("action")
        message := name + " is " + action
        c.String(http.StatusOK, message)
    })

    // 精准路由
    // √	/user/groups
    router.GET("/user/groups", func(c *gin.Context) {
        c.String(http.StatusOK, "exact route")
    })

    router.Run(":8080")
}