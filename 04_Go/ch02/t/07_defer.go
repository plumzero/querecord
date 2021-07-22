
package main

import (
	"time"
	"fmt"
)

func main() {
	
	{
		defer func() {
			fmt.Println("... defer")
		}()
	}

	time.Sleep(time.Second)

	fmt.Println("main over")
}