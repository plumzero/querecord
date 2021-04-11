
package main

import (
	"fmt"
	"encoding/json"
	"bytes"
)

type Book struct {
	Title string
	Authors []string
	Publisher string
	IsPublished bool
	Price float32
}

func main() {

	gobook := Book{
		"Golang programing",
		[]string{ "XuShiWei", "HughLv", "Pandaman", "GuaguaSong" },
		"ituring.com.cn",
		true,
		9.99,
	}

	b, err := json.Marshal(gobook)
	if err != nil {
		panic("Marshal")
	}

	bforcheck := []byte(
		`{
			"Golang programing",
			[ "XuShiWei", "HughLv", "Pandaman", "GuaguaSong" ],
			"ituring.com.cn",
			true,
			9.99,
		}`,
	)

	if bytes.Compare(b, bforcheck) != 0 {
		fmt.Println("ok")
	}
}