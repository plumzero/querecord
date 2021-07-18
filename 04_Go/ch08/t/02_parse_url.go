
package main

import (
	"net/url"
	"fmt"
)

func main() {
	path := "http://localhost:8082/article?id=1"
	p, _ := url.Parse(path)	// 解析 URL
	fmt.Println(p.Host)
	fmt.Println(p.User)
	fmt.Println(p.RawQuery)
	fmt.Println(p.RequestURI())
}