
package main

import (
	"errors"
	"time"
	"os"
	"fmt"
	"log"
)

func DivideTestLog(dividend float64, divisor float64) (result float64, err error) {
	if divisor == 0 {
		result = 0.0
		err = errors.New("own-defined runtime error: divide by zero")
		return
	}

	return dividend / divisor, nil
}

func DivideForRecoverLog(dividend float64, divisor float64) (result float64) {
	if divisor == 0 {
		err := errors.New("panic runtime error: divide by zero")
		panic(err)
		return
	}

	return dividend / divisor
}

func main() {
	file := time.Now().Format("2006-01-02") + ".txt"
	logFile, err := os.OpenFile(file, os.O_RDWR | os.O_CREATE | os.O_APPEND, 0766)
	if err != nil {
		fmt.Println(err)
	}

	logger := log.New(logFile, "error test ", log.Ldate | log.Lshortfile)
	r, e1 := DivideTestLog(6, 0)
	if e1 == nil {
		fmt.Println(r)
	} else {
		logger.Print(e1)
	}

	logger.SetPrefix("panic test ")
	defer func() {
		if e2 := recover(); e2 != nil {
			logger.Print(e2)
		}
	} ()

	r1 := DivideForRecoverLog(6, 0)
	fmt.Println(r1)
}
