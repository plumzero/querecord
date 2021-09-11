
package main

import (
	"time"
	"fmt"
)

func main() {
	hour, min, sec := time.Now().Clock()
	fmt.Printf("hour=%d,min=%d,sec=%d\n", hour, min, sec)

	hour, min, sec = time.Now().Add(-2 * time.Minute).Clock()
	fmt.Printf("hour=%d,min=%d,sec=%d\n", hour, min, sec)
}