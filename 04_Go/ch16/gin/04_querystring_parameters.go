package main

import (
    "net/http"
    "github.com/gin-gonic/gin"

	"fmt"
)

func main() {
	router := gin.Default()

	router.GET("/welcome", func(c *gin.Context) {
		firstname := c.DefaultQuery("firstname", "Guest")
		lastname := c.Query("lastname")

		fmt.Println("firstname =", firstname, " lastname =", lastname)
		c.String(http.StatusOK, "Hello %s %s", firstname, lastname)

		x := c.GetStringMapString("lastname")
		fmt.Println("  ------------ x = ", x)
	})

	router.Run(":8080")
}