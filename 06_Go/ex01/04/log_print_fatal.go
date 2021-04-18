
package main

import (
	"fmt"
	"log"
	"os"
	"time"
)

func main() {
	file := time.Now().Format("2006-01-02") + ".txt"
	logFile, err := os.OpenFile(file, os.O_RDWR | os.O_CREATE | os.O_APPEND, 0766)
	if err != nil {
		fmt.Println(err)
	}

	logger := log.New(logFile, "as-a-prefix ", log.Ldate | log.Lshortfile)
	
	logger.Print("print a log information")

	fmt.Println(logger.Flags())
	logger.SetFlags(log.LstdFlags | log.Lshortfile)
	fmt.Println(logger.Flags())

	fmt.Println(logger.Prefix())
	logger.SetPrefix("prefix-after-modified ")

	logger.Output(2, "print a log information")
	logger.Printf("line %d: %s", 33, "format print")
	logger.Println("print with newline")
	logger.Print("standard print")
	logger.Fatal("fatal print")
}