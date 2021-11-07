
package main

import (
	"github.com/gin-gonic/gin"
	"net/http"
	"log"
	"os"
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

	cssfile := "/ajax_helper.css"
	jsfile := "/ajax_helper.js"

	router.StaticFile(cssfile, csp + cssfile)
	router.StaticFile(jsfile, jsp + jsfile)

	router.LoadHTMLGlob(hmp + "/*")

    router.GET("/", func(c *gin.Context) {
        c.HTML(http.StatusOK, "ajax_helper.html", nil)
    })

	router.Run(":8080")
}