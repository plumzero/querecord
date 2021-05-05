
package main

import (
	"io"
	"log"
	"net/http"
	"os"
	// "fmt"
)

const (
	UPLOAD_DIR = "./uploads"
	
	UPLOAD_METHOD_GET_STRING = 
	`<form action="/upload" method="POST" enctype="multipart/form-data">` +
    	`Choose an image to upload: <input type="file" name="image">` +
    	`<input type="submit" value="Upload">` +
	`</form>`
)

func uploadHandler(w http.ResponseWriter, r *http.Request) {
	if r.Method == "GET" {
		io.WriteString(w, UPLOAD_METHOD_GET_STRING)
		return
	}

	if r.Method == "POST" {
		// 接收到来自客户端的 POST 请求，从表单中寻找名为 image 的文本域
		f, h, err := r.FormFile("image")	// return multipart.File *multipart.FileHeader error
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		filename := h.Filename
		defer f.Close()
		// 创建临时文件
		t, err := os.Create(UPLOAD_DIR + "/" + filename)
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		defer t.Close()
		// 创建副本
		if _, err := io.Copy(t, f); err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		// 跳转到查看图片页面
		http.Redirect(w, r, "/view?id=" + filename, http.StatusFound)
	}
}

func main() {
	http.HandleFunc("/upload", uploadHandler)
	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		log.Fatal("ListenAndServe: ", err.Error())
	}
}
