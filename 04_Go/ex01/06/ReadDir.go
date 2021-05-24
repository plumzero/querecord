
package main

import (
	"io/ioutil"
	"fmt"
)

func main() {
	files, err := ioutil.ReadDir(".")
	if err != nil {
		panic(err)
	}
	
	for _, file := range files {
		fmt.Println("filename:", file.Name())
	}
}
