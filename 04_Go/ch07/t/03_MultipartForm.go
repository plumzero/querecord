
package main

import (
	"net/http"
	"html/template"
	"io/ioutil"
	"log"
	"fmt"
)

func upload(w http.ResponseWriter, r *http.Request) {
	if r.Method == "GET" {
		t, _ := template.ParseFiles("03_MultipartForm.html")
		t.Execute(w, nil)
	}

	if r.Method == "POST" {
		r.ParseMultipartForm(4096)
		// 获取名为 "uploaded" 的第 1 个文件头
		fileHeader := r.MultipartForm.File["uploaded"][0]
		file, err := fileHeader.Open()		// 获取文件
		if err != nil {
			fmt.Println(err)
			return
		}
		data, err := ioutil.ReadAll(file)	// 读取文件
		if err != nil {
			fmt.Println(err)
			return
		}
		fmt.Fprintf(w, string(data))
	}
}

func main() {
	http.HandleFunc("/upload", upload)
	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		log.Fatal("ListenAndServe:", err)
	}
}