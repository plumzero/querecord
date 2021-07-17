
package main

import (
	"bytes"
	"fmt"
	"io/ioutil"
	"net/http"
)

func main() {
	url := "https://www.----"
	body := "{}"		// 一条 json 数据
	response, err := http.Post(url, "application/x-www-form-urlencoded", bytes.NewBuffer([]byte(body)))
	if err != nil {
		fmt.Println("err", err)
	}
	if response.StatusCode != http.StatusOK {
		fmt.Println("status code:", response.StatusCode)
	}
	b, err := ioutil.ReadAll(response.Body)
	if err == nil {
		fmt.Println(string(b))
	}
}