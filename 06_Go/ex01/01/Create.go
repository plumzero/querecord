
package main

import (
	"log"
	"os"
)

func main() {

	var fname string = "filefortest.txt"

	file, err := os.Create(fname)
	if err != nil {
		log.Fatal(err)
	}

	defer file.Close()
}
