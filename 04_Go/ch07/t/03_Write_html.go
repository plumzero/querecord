
package main

import (
	"net/http"
	"fmt"
)

func Home(w http.ResponseWriter, r *http.Request) {
	html := `<html>
		<head>
			<title>用 Write() 方法返回 html 文档</title>
		</head>
		<body>
			<h1>Hello World</h1>
		</body>
		</html>`
	
	w.Write([]byte(html))
}

func main() {
	http.HandleFunc("/home", Home)
	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		fmt.Println(err)
	}
}