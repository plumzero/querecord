
package main

import (
	"net/http"
	"github.com/gin-contrib/sessions"
	"github.com/gin-contrib/sessions/cookie"
	"github.com/gin-gonic/gin"
)

func main() {
	r := gin.Default()
	// 创建基于 cookie 的存储引擎，passsword123456 参数是用于加密的密钥
	store := cookie.NewStore([]byte("password123456"))
	// 设置 session 中间件，参数 my_session 指的是 session 的名字，也是 cookie 的名字
	// store 是前面创建的存储引擎，可以将其替换成其他存储引擎
	r.Use(sessions.Sessions("my_session", store))

	r.GET("/hello", func(c *gin.Context) {
		// 初始化 session 对象
		session := sessions.Default(c)
		// 通过 session.Get() 函数读取 session 值
		// session 是键值对格式数据，因此需要通过 key 查询数据
		if session.Get("hello") != "world" {
			// 设置 session 数据
			session.Set("hello", "world")
			// 删除 session 数据
			session.Delete("DaHuang")
			// 保存 session 数据
			session.Save()
			// 删除整个 session
			// session.Clear()
		}

		c.JSON(http.StatusOK, gin.H{ "hello": session.Get("hello") })
	})

	r.Run(":8080")
}