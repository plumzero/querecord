
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

	cssfile := "/ajax_global.css"
	jsfile := "/ajax_global.js"

	router.StaticFile(cssfile, csp + cssfile)
	router.StaticFile(jsfile, jsp + jsfile)

	tstfile := "/ajax/test.html"
	router.StaticFile(tstfile, pwd + tstfile)
	misfile := "/ajax/missing.html"
	router.StaticFile(misfile, pwd + misfile)

	router.LoadHTMLGlob(hmp + "/*")

    router.GET("/", func(c *gin.Context) {
        c.HTML(http.StatusOK, "ajax_global.html", nil)
    })

	router.Run(":8080")
}