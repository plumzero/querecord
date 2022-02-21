
package main

import (
	"time"
	"fmt"
	"strconv"
)

func main() {
	hour, min, sec := time.Now().Clock()
	fmt.Printf("hour=%d,min=%d,sec=%d\n", hour, min, sec)
	fmt.Printf("hour-min=%s\n", fmt.Sprintf("%02d%02d", hour, min))
	hourmin, _ := strconv.Atoi(fmt.Sprintf("%02d%02d", hour, min))
	fmt.Printf("int %d\n", hourmin)

	hour, min, sec = time.Now().Add(-2 * time.Minute).Clock()
	fmt.Printf("hour=%d,min=%d,sec=%d\n", hour, min, sec)
}