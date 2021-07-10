
package main

import (
	"fmt"
	"log"
	"net/http"
)

func hiHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Hi, Go HandleFunc")
}

type welcomeHandler struct {
	Name string
}

func (h welcomeHandler) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "hi, %s", h.Name)
}

func main() {
	mux := http.NewServeMux()
	// 注册处理器函数
	mux.HandleFunc("/hi", hiHandler)

	// 注册处理器
	mux.Handle("/welcome/goweb", welcomeHandler{Name: "Hi, Go Handle"})

	server := &http.Server{
		Addr: ":8080",
		Handler: mux,
	}

	if err := server.ListenAndServe(); err != nil {
		log.Fatal(err)
	}
}