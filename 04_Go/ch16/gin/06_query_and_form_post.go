
package main

import (
	"net/http"
    "github.com/gin-gonic/gin"
	"strings"
)

// 在浏览器上输入 http://a.b.c.d:8080/form_post

// http://192.168.3.7:8080/form_post?id=123&page=1000

func main() {
	router := gin.Default()
	router.LoadHTMLGlob("templates/*")

	router.GET("/form_post", func(c *gin.Context) {
		c.HTML(http.StatusOK, "form_post.html", nil)
	})

	router.POST("form_post", func(c *gin.Context) {
		if c.Query("redirect") == "" {
			referer := c.Request.Header.Get("Referer")
			c.Redirect(http.StatusTemporaryRedirect, "/form_post" + referer[strings.IndexByte(referer, '?'):] + "&redirect=1")
		} else {
			id := c.Query("id")
			page := c.DefaultQuery("page", "0")
			
			name := c.PostForm("name")
			message := c.DefaultPostForm("message", "null")
	
			c.JSON(200, gin.H{
				"status": "posted",
				"id": id,
				"page": page,
				"name": name,
				"message": message,
			})
		}
	})

	router.Run(":8080")
}