
package main

import (
	"log"
	"os"
	"fmt"
)

func main() {

	var fname string = "filefortest.txt"

	file, err := os.OpenFile(fname, os.O_RDWR | os.O_CREATE, 0644)
	if err != nil {
		log.Fatal(err)
		return
	}

	defer file.Close()

	if _, err := file.Write([]byte("write some data\n")); err != nil {
		log.Fatal(err)
	}

	fmt.Println("===== test over =====")
}
