
package main

import (
	"net/http"
    "github.com/gin-gonic/gin"
)

// curl -F "name=XiaoMing;message=Pick" http://127.0.0.1:8080/form_post
// 或者在浏览器上输入 http://a.b.c.d:8080/form_post

func main() {
	router := gin.Default()
	router.LoadHTMLGlob("templates/*")

	router.GET("/form_post", func(c *gin.Context) {
		c.HTML(http.StatusOK, "form_post.html", nil)
	})

	router.POST("/form_post", func(c *gin.Context) {
		name := c.PostForm("name")
		message := c.DefaultPostForm("message", "null")

		c.JSON(200, gin.H{
			"status": "posted",
			"name": name,
			"message": message,
		})
	})

	router.Run(":8080")
}