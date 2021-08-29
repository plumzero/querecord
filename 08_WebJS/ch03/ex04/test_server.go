package main

import (
    "net/http"
    "github.com/gin-gonic/gin"
)

func PostCallback(c *gin.Context) {
    buf := make([]byte, 1024)
    n, _ := c.Request.Body.Read(buf)

    c.Header("Access-Control-Allow-Origin",      "*")
    c.Header("Access-Control-Allow-Headers",     "Origin, X-Requested-With, Content-Type, Accept")

    c.JSON(200, gin.H{
        "Post": string(buf[0:n]),
    })

    return
}

func main() {
    router := gin.Default()

    router.GET("/api/v1/red", func(c *gin.Context) {
        c.Header("Access-Control-Allow-Origin",      "*")
        c.Header("Access-Control-Allow-Headers",     "Origin, X-Requested-With, Content-Type, Accept")
        c.String(http.StatusOK, "Get is red")
    })

    router.POST("api/v1/blue", PostCallback)

    router.Run(":8080")
}
