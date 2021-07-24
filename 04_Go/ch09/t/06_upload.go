
package main

import (
	"fmt"
    "net/http"
    "github.com/gin-gonic/gin"
)

func main() {
	router := gin.Default()
	router.LoadHTMLGlob("./*")

	// 设置文件上传大小限制，默认是 32 MB
	router.MaxMultipartMemory = 64 << 20	// 64 MB

    router.GET("/upload", func(c *gin.Context) {
        c.HTML(http.StatusOK, "06_upload.html", nil)
    })


	router.POST("/upload", func(c *gin.Context) {
		file, _ := c.FormFile("uploaded")
		fmt.Println(file.Filename)

		// 将上传的文件保存到 /tmp/hello 文件中
		c.SaveUploadedFile(file, "/tmp/hello")
		c.String(http.StatusOK, fmt.Sprintf("'%s' uploaded!", file.Filename))
	})

	router.Run(":8080")
}
