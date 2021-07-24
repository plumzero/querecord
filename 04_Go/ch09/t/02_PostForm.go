
package main

import (
    "net/http"
    "github.com/gin-gonic/gin"
)

// 浏览器中输入 IP:8080/post/form
func emailUrl(c *gin.Context) {
	email := c.PostForm("mye")
	id := c.DefaultPostForm("myi", "8864")

	url, ok := c.GetPostForm("myu")
	if ! ok {
		// ... url 不存在
	}

    c.String(http.StatusOK, "email=%s,id=%s,url=%s", email, id, url)
}

func main() {
    router := gin.Default()
    router.LoadHTMLGlob("./*")		// 加载当前路径下的所有 html

    router.GET("/post/form", func(c *gin.Context) {
        c.HTML(http.StatusOK, "02_PostForm.html", nil)
    })

    router.POST("/post/form", emailUrl)

    router.Run(":8080")
}