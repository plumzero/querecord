
package main

import (
	"io/ioutil"
	"path"
	"fmt"
)

func main() {
	files, err := ioutil.ReadDir(".")
	if err != nil {
		panic(err)
		return
	}

	for _, fi := range files {
		fname := fi.Name()
		fmt.Println("base =", path.Base(fname), "ext =", path.Ext(fname))
	}
}