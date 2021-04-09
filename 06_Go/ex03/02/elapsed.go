
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

	var ticks int64 = elapsed.Milliseconds()
	fmt.Println(ticks)

	// 再休眠一会
	timeleft := 3000 - ticks
	if timeleft > 0 {
		time.Sleep(time.Duration(timeleft) * time.Millisecond)
	}
}