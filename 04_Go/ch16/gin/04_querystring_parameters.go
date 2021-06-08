package main

import (
    "net/http"
    "github.com/gin-gonic/gin"
)

// 注意，使用 curl 测试时 url 字符串两边用引号(单引号或双引号)括起来
// curl "http://127.0.0.1:8080/welcome?firstname=Jane&lastname=Doe"

func main() {
	router := gin.Default()

	router.GET("/welcome", func(c *gin.Context) {
		firstname := c.DefaultQuery("firstname", "Guest")
		lastname := c.Query("lastname")

		c.String(http.StatusOK, "Hello %s %s", firstname, lastname)
	})

	router.Run(":8080")
}