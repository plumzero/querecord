
package main

import (
	"fmt"
	"strings"
	"time"
)

func main() {
	{
		logname := time.Now().Format("2006-01-02") + ".test.log"

		fmt.Println("logname =", logname)
	
		index := strings.IndexByte(logname, '.')
	
		before := logname[:index]
		after := logname[index:]
	
		fmt.Println("before = ", before)
		fmt.Println("after = ", after)
	}

	{
		logname := "./tmp/2021-05-19.dev.log"
		
		index := strings.LastIndexByte(logname, '/')

		before := logname[:index + 1]
		after := logname[index + 1:]

		fmt.Println("before = ", before)
		fmt.Println("after = ", after)
	}
}

