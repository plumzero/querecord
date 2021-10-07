package main

import (
	"net/http"
	"log"

    "github.com/gin-gonic/gin"
)

var b = []byte(
	`[
		{
			"term": "BACCHUS",
			"part": "n.",
			"definition": "A convenient deity invented by the...",
			"quote": [
				"Is public worship, then, a sin,",
				"That for devotions paid to Bacchus",
				"The lictors dare to run us in,",
				"And resolutely thump and whack us?"
			],
			"author": "Jorace"
		},
		{
			"term": "BACKBITE",
			"part": "v.t.",
			"definition": "To speak of a man as you find him when..."
		},
		{
			"term": "BEARD",
			"part": "n.",
			"definition": "The hair that is commonly cut off by..."
		}
	]`,
)


func goLogin(c *gin.Context) {
    name := c.PostForm("name")
    password := c.PostForm("pwd")

    c.String(http.StatusOK, "username=%s,password=%s", name, password)
}

// func main() {
//     router := gin.Default()
//     router.LoadHTMLGlob("./*")		// 加载当前路径下的所有 html

//     router.GET("/user/login", func(c *gin.Context) {
//         c.HTML(http.StatusOK, "01_handlerfunc.html", nil)
//     })

//     router.POST("/user/login", goLogin)

//     router.Run(":8080")
// }

func main() {
    router := gin.Default()

	router.Static("/t", "/home/github/ldev/28_jQuery/ch05/t")
	// router.StaticFS("/t", http.Dir("/home/github/ldev/28_jQuery/ch05"))
	router.LoadHTMLGlob("*")


    router.GET("/get", func(c *gin.Context) {
		log.Println("=========================")
        c.String(http.StatusOK, string(b))
    })

	router.GET("/", func(c *gin.Context) {
		c.HTML(http.StatusOK, "index.html", nil)
	})

    router.Run(":8080")
}