
package main

import (
	"log"
	"os"
	"fmt"
)

func main() {

	var fname string = "filefortest.txt"

	file, err := os.Open(fname)
	if err != nil {
		log.Fatal(err)
		return
	}

	defer file.Close()

	data := make([]byte, 100)
	count, err := file.Read(data)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Printf("read %d bytes: %s\n", count, data[:count])
}
