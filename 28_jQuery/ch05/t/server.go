package main

import (
	"net/http"
	"log"

    "github.com/gin-gonic/gin"
)

var bs = []byte(
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
		}
	]`,
)

var cs = []byte(
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

func main() {
    router := gin.Default()

	router.Static("/t", "../t")
	router.LoadHTMLGlob("*")


    router.GET("/get", func(c *gin.Context) {
        c.String(http.StatusOK, string(bs))
	})
	
    router.POST("/post", func(c *gin.Context) {
		appId := c.PostForm("appId")
		userId := c.PostForm("userId")
		log.Printf("appId=%s,userId=%s", appId, userId)
		c.String(http.StatusOK, string(cs))
	})

	router.GET("/", func(c *gin.Context) {
		c.HTML(http.StatusOK, "index.html", nil)
	})

    router.Run(":8080")
}