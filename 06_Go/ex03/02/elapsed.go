
package main

import (
	"time"
	"fmt"
)

func main() {

	start := time.Now()

	time.Sleep(101 * time.Millisecond)

	end  := time.Now()

	elapsed := end.Sub(start)

	var count int64 = elapsed.Milliseconds()

	fmt.Println(count)
}