
package main

import (
	"time"
	"os"
	"log"
)

func main() {
	file := time.Now().Format("2006-01-02") + ".txt"
	logFile, err := os.OpenFile(file, os.O_RDWR | os.O_CREATE | os.O_APPEND, 0766)
	if err != nil {
		panic(err)
	}

	logger := log.New(logFile, "as-a-prefix ", log.Ldate | log.Lshortfile)

	logger.Output(2, "panic test")
	logger.Panicln("panic exit")
}