
package main

import (
	"time"
	"fmt"
)

func main() {

	start := time.Now()

	time.Sleep(101 * time.Millisecond)

	elapsed := time.Since(start).Milliseconds()

	fmt.Println("elapsed =", elapsed)
}