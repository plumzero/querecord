
package main

import (
	"io/ioutil"
	"net/http"
	"fmt"
	"mime"
)

func main() {
	{
		content, err := ioutil.ReadFile("testdata/b1.png")
		if err != nil {
			fmt.Println(err)
		}
		mime_type := http.DetectContentType(content)
		
		mediatype, params, err := mime.ParseMediaType(mime_type)
		if err != nil {
			panic(err)
		}
	
		fmt.Println("b1.png 's type:", mediatype, ", charset:", params["charset"])
	}

	{
		content, err := ioutil.ReadFile("testdata/temp.txt")
		if err != nil {
			fmt.Println(err)
		}
		mime_type := http.DetectContentType(content)
	
		mediatype, params, err := mime.ParseMediaType(mime_type)
		if err != nil {
			panic(err)
		}
	
		fmt.Println("temp.txt 's type:", mediatype, ", charset:", params["charset"])
	}
}
