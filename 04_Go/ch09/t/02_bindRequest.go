
package main

import (
	"net/http"
    "github.com/gin-gonic/gin"
)

// 浏览器中输入 IP:8080/user/info

type UserInfo struct {
	Name string 		`json:"name" form:"name"`
	Age	string			`json:"age" form:"age"`
	Phone string		`json:"phone" form:"phone"`
}

func GetInfo(c *gin.Context) {
	u := UserInfo{}

	if c.ShouldBind(&u) == nil {
		// bind success
	}

    c.String(http.StatusOK, "user=%v", u)
}

func main() {
    router := gin.Default()
    router.LoadHTMLGlob("./*")		// 加载当前路径下的所有 html

    router.GET("/user/info", func(c *gin.Context) {
        c.HTML(http.StatusOK, "02_bindRequest.html", nil)
    })

    router.POST("/user/info", GetInfo)

    router.Run(":8080")
}