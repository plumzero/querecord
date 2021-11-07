
package main

import (
	"github.com/gin-gonic/gin"
	"net/http"
	"log"
	"os"
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

func init() {
	log.SetFlags(log.LstdFlags|log.Lshortfile|log.Lmicroseconds)
}

func main() {
	router := gin.Default()

	pwd, _ := os.Getwd()

	hmp := pwd + "/html"
	csp := pwd + "/css"
	jsp := pwd + "/js"

	cssfile := "/ajax_handy.css"
	jsfile := "/ajax_handy.js"

	router.StaticFile(cssfile, csp + cssfile)
	router.StaticFile(jsfile, jsp + jsfile)

	xmlfile := "/ajax/get.xml"
	router.StaticFile(xmlfile, pwd + xmlfile)
	jsofile := "/ajax/getJSON.json"
	router.StaticFile(jsofile, pwd + jsofile)
	jstfile := "/ajax/getScript.js"
	router.StaticFile(jstfile, pwd + jstfile)
	hmtfile := "/ajax/load.html"
	router.StaticFile(hmtfile, pwd + hmtfile)

	router.LoadHTMLGlob(hmp + "/*")

    router.GET("/", func(c *gin.Context) {
        c.HTML(http.StatusOK, "ajax_handy.html", nil)
    })

    router.GET("/get", func(c *gin.Context) {
        c.String(http.StatusOK, string(bs))
	})

    router.POST("/post", func(c *gin.Context) {
		appId := c.PostForm("appId")
		userId := c.PostForm("userId")
		log.Printf("appId=%s,userId=%s", appId, userId)
		c.String(http.StatusOK, string(cs))
	})

	router.Run(":8080")
}