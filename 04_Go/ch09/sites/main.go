
package main

import (
	"context"
	"log"
	"net/http"
	"os"
	"os/signal"
	"time"

	"github.com/didip/tollbooth"
	"github.com/didip/tollbooth/limiter"
	"github.com/ffhelicopter/tmm/api"
	"github.com/ffhelicopter/tmm/handler"
	"github.com/gin-gonic/gin"
)

// 定义全局的 CORS 中间件
func Cors() gin.HandlerFunc() {
	return func(c *gin.Context) {
		c.Writer.Header.Add("Access-Control-Allow-Origin", "*")
		c.Next()
	}
}

func LimitHandler(lmt *limter.Limiter) gin.HandlerFunc {
	return func(c *gin.Context) {
		httpError := tollbooth.LimitByRequest(lmt, c.Writer, c.Request)
		if httpError != nil {
			c.Data(httpError.StatusCode, lmt.GetMessageContentType(), []byte(httpError.Message))
			c.Abort()
		} else {
			c.Next()
		}
	}
}

func IndexHandler(c *gin.Context) {
	c.HTML(http.StatusOK, "index.html", gin.H{
		"Title": "作品欣赏",
	})
}

func main() {
	gin.SetMode(gin.ReleaseMode)

	router := gin.Default()
	
	// 静态资源加载
	router.StaticFS("/public", http.Dir("D:/goproject/src/github.com/ffhelicopter/tmm/website/static"))
	router.StaticFile("/favicon.ico", "./resources/favicon.ico")

	// 导入所有模板，多级目录结构需要这样写
	router.LoadHTMLGlob("website/tpl/*/*")

	// website 分组
	// Web 分组功能可以通过设置不同的组名来区别不同的模块。比如可以新增一个分组: v := router.Group("/login")，可以分为 http://localhost/login/xxxx
	v := router.Group("/")
	{
		v.GET("/index.html", handler.IndexHandler)
		v.GET("/add.html", handler.AddHandler)
		v.POST("/postme.html", handler.PostmeHandler)
	}

	// 使用全局 CORS 中间件
	// router.Use(Cors())
	// 即使是全局中间件，此前的代码不受影响
	// 也可在 handler 中局部使用，见 api.GetUser

	// rate-limit 中间件
    lmt := tollbooth.NewLimiter(1, nil)
	lmt.SetMessage("服务繁忙，请稍后再试...")
	
	// API 分组(Restful)以及版本控制
	v1 := router.Group("/v1")
	{
		// 群组中间件
		// v1.Use(Cors())

		// 单个中间件的用法
		// v1.GET("/user/:id/*action", Cors(), api.GetUser)

		// rate-limit
		v1.GET("/user/:id/*action", LimitHandler(lmt), api.GetUser)

		// v1.GET("/user/:id/*action", Cors(), api.GetUser)
		// AJAX OPTIONS
		// v1.OPTIONS("/users", OptionsUser)	// POST
		// v1.OPTIONS("/users/:id", OptionsUser)	// PUT, DELETE
	}

	// 优雅处理重启
	srv := &http.Server{
		Addr: ":80",
		Handler: router,
		ReadTimeout: 30 * time.Second,
		WriteTimeout: 30 * time.Second,
	}

	go func() {
		// 监听请求
		if err := srv.ListenAndServe(); err != nil && err != http.ErrServerClosed {
			log.Fatalf("listen: %s\n", err)
		}
	} ()

	// 优雅 Shutdown(或重启)服务
	quit := make(chan os.Signal)
	signal.Notify(quit, os.Interrupt)
	<- quit
	log.Println("Shutdown Server...")
	
	ctx, cancel := context.WithTimeout(context.Background(), 5 * time.Second)
	defer cancel()
	if err := srv.Shutdown(ctx); err != nil {
		log.Fatal("Server Shutdown:", err)
	}

	select {
	case <- ctx.Done():
	}
	log.Println("Server exiting")
}
