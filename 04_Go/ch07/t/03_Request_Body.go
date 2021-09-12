
package main

import (
	"fmt"
	"net/http"
)

// 分别按如下方法执行，查看结果
// 	curl http://127.0.0.1:8080/getBody -X POST -d "hi=web"
//	curl http://127.0.0.1:8080/getBody
func getBody(w http.ResponseWriter, r *http.Request) {
	// 获取请求报文的内容长度
	len := r.ContentLength
	fmt.Println("r.Method =", r.Method)
	// 读取请求体
	body := make([]byte, len)
	r.Body.Read(body)
	fmt.Fprintf(w, string(body))
}

func main() {
	http.HandleFunc("/getBody", getBody)
	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		fmt.Println(err)
	}
}
