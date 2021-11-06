
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

	cssfile := "/types.css"
	jsfile := "/types.js"

	router.StaticFile(cssfile, csp + cssfile)
	router.StaticFile(jsfile, jsp + jsfile)
	router.LoadHTMLGlob(hmp + "/*")

    router.GET("/", func(c *gin.Context) {
        c.HTML(http.StatusOK, "types.html", nil)
    })

	router.Run(":8080")
}