
package main

import (
	"io/ioutil"
	"net/http"
	"fmt"
)

func main() {
	{
		content, err := ioutil.ReadFile("testdata/b1.png")
		if err != nil {
			fmt.Println(err)
		}
		mime_type := http.DetectContentType(content)
	
		fmt.Println("b1.png 's mime type:", mime_type)
	}
	{
		content, err := ioutil.ReadFile("testdata/temp.txt")
		if err != nil {
			fmt.Println(err)
		}
		mime_type := http.DetectContentType(content)
	
		fmt.Println("temp.txt 's mime type:", mime_type)
	}
	{
		content, err := ioutil.ReadFile("testdata/program.c")
		if err != nil {
			fmt.Println(err)
		}
		mime_type := http.DetectContentType(content)
	
		fmt.Println("program.c 's type:", mime_type)
	}
	{
		content, err := ioutil.ReadFile("testdata/binexe")
		if err != nil {
			fmt.Println(err)
		}
		mime_type := http.DetectContentType(content)
	
		fmt.Println("binexe 's type:", mime_type)
	}
	{
		content, err := ioutil.ReadFile("testdata/conftest.json")
		if err != nil {
			fmt.Println(err)
		}
		mime_type := http.DetectContentType(content)
	
		fmt.Println("conftest.json 's type:", mime_type)
	}
}