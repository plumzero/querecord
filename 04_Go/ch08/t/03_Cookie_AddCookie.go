
package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
	"net/url"
	"strings"
)

func main() {
	CopeHandle("GET", "https://www.baidu.com", "")
}

// HTTP 请求处理
func CopeHandle(method, urlVal, data string) {
	client := &http.Client{}
	var req *http.Request

	if data == "" {
		urlArr := strings.Split(urlVal, "?")
		if len(urlArr) == 2 {
			urlVal = urlArr[0] + "?" + getParseParam(urlArr[1])
		}
		req, _ = http.NewRequest(method, urlVal, nil)
	} else {
		req, _ = http.NewRequest(method, urlVal, strings.NewReader(data))
	}

	cookie := &http.Cookie{Name: "X-Hello", Value: "abcdefghijklmnopqrstuvwxyz", HttpOnly: true}
	req.AddCookie(cookie)

	req.Header.Add("X-Hello", "1234567890")
	resp, err := client.Do(req)
	if err != nil {
		fmt.Println(err)
	}

	defer resp.Body.Close()
	b, _ := ioutil.ReadAll(resp.Body)
	fmt.Println(string(b))
}

// 将 GET 请求的参数进行转义
func getParseParam(param string) string {
	return url.PathEscape(param)
}
