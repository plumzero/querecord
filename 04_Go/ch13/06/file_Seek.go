
package main

import (
	"log"
	"os"
	"fmt"
	"io"
)

func main() {

	var fname string = "filefortest.txt"

	file, err := os.Open(fname)
	if err != nil {
		log.Fatal(err)
		return
	}

	defer file.Close()

	// Use io.SeekStart, io.SeekCurrent, and io.SeekEnd.
	_, err = file.Seek(3, io.SeekStart)
	if err != nil {
		log.Fatal(err)
	}

	data := make([]byte, 100)
	count, err := file.Read(data)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Printf("read %d bytes: %s\n", count, string(data))
}
