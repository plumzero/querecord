
package main

import (
	"time"
	"fmt"
)

func main() {

	{
		fmt.Println(time.Now().Unix(), time.Now().UnixNano() / 1000000)

		time.Sleep(100 * time.Millisecond)
	
		fmt.Println(time.Now().Unix(), time.Now().UnixNano() / 1000000)
	}
}