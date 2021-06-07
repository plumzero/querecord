package main

import (
    "net/http"
    "github.com/gin-gonic/gin"
    "fmt"
)

func PostCallback(c *gin.Context) {

    buf := make([]byte, 1024)
    n, _ := c.Request.Body.Read(buf)
    fmt.Println(string(buf[0:n]))

    c.JSON(200, gin.H{
        "Post": string(buf[0:n]),
    })

    return
}

func main() {
    router := gin.Default()

    // curl http://127.0.0.1:8080/api/v1/red
    router.GET("/api/v1/red", func(c *gin.Context) {
        c.String(http.StatusOK, "Get is red")
    })

    // curl -X POST http://127.0.0.1:8080/api/v1/blue -d'{"username" : "ultraboy", "userage" : "20394"}'
    router.POST("api/v1/blue", PostCallback)

    router.Run(":8080")
}
