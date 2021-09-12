
package main

import (
	"net/http"
	"github.com/gin-gonic/gin"
)

func main() {
	router := gin.Default()

	router.StaticFS("/public", http.Dir("/tmp"))
	router.StaticFile("/my.ico", "./resouces/my.ico")

	router.Run(":8080")
}