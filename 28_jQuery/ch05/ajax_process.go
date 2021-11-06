
package main

import (
	"github.com/gin-gonic/gin"
	"net/http"
	"path"
	"log"
	"os"
)

func init() {
	log.SetFlags(log.LstdFlags|log.Lshortfile|log.Lmicroseconds)
}

func main() {
	router := gin.Default()

	pwd, _ := os.Getwd()

	hmp := path.Dir(pwd) + "/html"
	csp := path.Dir(pwd) + "/css"
	jsp := path.Dir(pwd) + "/js"

	cssfile := "/ajax_process.css"
	jsfile := "/ajax_process.js"

	router.StaticFile(cssfile, csp + cssfile)
	router.StaticFile(jsfile, jsp + jsfile)

	tstfile := "/ajax/test.html"
	router.StaticFile(tstfile, pwd + tstfile)

	router.LoadHTMLGlob(hmp + "/*")

    router.GET("/", func(c *gin.Context) {
        c.HTML(http.StatusOK, "ajax_process.html", nil)
    })

	router.POST("/post_nofify", func(c *gin.Context) {
		name := c.PostForm("name")
		location := c.PostForm("location")
		log.Println("received:", name, location);
		c.String(http.StatusOK, "username=%s,location=%s", name, location)
	});

	router.Run(":8080")
}