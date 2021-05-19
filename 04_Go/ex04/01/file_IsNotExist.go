package main

import (
	"fmt"
	"os"
)

func main() {
	filename := "filefortest.txt"
	if _, err := os.Stat(filename); os.IsNotExist(err) {
		fmt.Println("file does not exist")
	}
}
