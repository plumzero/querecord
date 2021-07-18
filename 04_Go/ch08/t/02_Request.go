package main

import (
	"fmt"
	"log"
	"net/http"
	"strings"
)

func request(w http.ResponseWriter, r *http.Request) {
	fmt.Println("Request 解析")
	// HTTP Method
	fmt.Println("method", r.Method)
	// RequestURI 是被客户端发送到服务器的请求行中未修改的请求 URI
	fmt.Println("RequestURI:", r.RequestURI)
	// URI 类型，下方分别列出 URL 的各成员
	fmt.Println("URL.Path", r.URL.Path)
	fmt.Println("URL.RawQuery", r.URL.RawQuery)
	fmt.Println("URL.Fragment", r.URL.Fragment)
	// 协议版本
	fmt.Println("proto", r.Proto)
	fmt.Println("ProtoMajor", r.ProtoMajor)
	fmt.Println("ProtoMinor", r.ProtoMinor)
	// HTTP 请求头
	for k, v := range r.Header {
		for _, vv := range v {
			fmt.Println("header key:" + k + " value:" + vv)
		}
	}
	// 判断是否为 multipart
	isMultipart := false
	for _, v := range r.Header["Content-Type"] {
		if strings.Index(v, "multipart/form-data") != -1 {
			isMultipart = true
		}
	}
	// 解析 Form 表单
	if isMultipart == true {
		r.ParseMultipartForm(128)
		fmt.Println("解析方式: ParseMultipartForm")
	} else {
		r.ParseForm()
		fmt.Println("解析方式: ParseForm")
	}
	// HTTP Body 内容长度
	fmt.Println("ContentLength", r.ContentLength)
	// 是否在回复请求后关闭连接
	fmt.Println("Close", r.Close)
	// HOST
	fmt.Println("host", r.Host)
	// 该请求的来源地址
	fmt.Println("RemoteAddr", r.RemoteAddr)

	fmt.Fprintf(w, "hello, let's go!")	// 这个是输出到客户端
}

func main() {
	http.HandleFunc("/hello", request)
	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		log.Fatal("ListenAndServe:", err)
	}
}