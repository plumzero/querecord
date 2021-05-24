
package main

import (
	"io/ioutil"
	"fmt"
)

func main() {
	content, err := ioutil.ReadFile("testdata/temp.txt")
	if err != nil {
		panic(err)
	}
	fmt.Printf("File contents: %s", content)
}
