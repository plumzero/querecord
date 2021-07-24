
package main

import (
	"fmt"
	"net/http"
)

func testHandle(w http.ResponseWriter, r *http.Request) {
	c, err := r.Cookie("test_cookie")
	fmt.Printf("cookie:%#v, err:%v\n", c, err)	// 客户端第一次请求时，这里打印为空，服务端在接下来设置 cookie 发往客户端。在接下来的请求中，这里打印不再为空。
												// 服务端按如下方式设置了 cookie 后，接下来的请求中 Path，Domain Expires 打印为空，这说明客户端并没有将这些发送过来，但实际
												// 		上它们确实是保存在客户端上的。

	cookie := &http.Cookie{
		Name: "test_cookie",
		Value: "abcdefghijklmnopqrstuvwxyz",
		MaxAge: 3600,
		Domain: "192.168.43.113",
		Path: "/",
	}

	http.SetCookie(w, cookie)

	// 应在具体数据返回之前设置 cookie，否则会设置失败
	w.Write([]byte("Hello"))
}

func main() {
	http.HandleFunc("/", testHandle)
	http.ListenAndServe(":8080", nil)
}