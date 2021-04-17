
package main

import (
	"fmt"
	"os"
	"bufio"
	"log"
	"io"
)

func main() {

	var fname string = "filefortest.txt"

	file, err := os.OpenFile(fname, os.O_RDWR | os.O_CREATE, 0644)
	if err != nil {
		log.Fatal(err)
		return
	}

	defer file.Close()

	reader := bufio.NewReader(file)
	if reader == nil {
		log.Fatal(err)
		return
	}

	for {
		line, _, err := reader.ReadLine()
		if err != nil {
			if err == io.EOF {
				fmt.Println("read over")
			}
			break;
		}

		fmt.Printf(string(line) + "\n")
	}

	fmt.Println("===== test over =====")
}