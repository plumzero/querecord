
package main

import (
	"fmt"
	"time"
)

func main() {
	// 创建一个一个定时器，每秒钟执行一次
	ticker := time.NewTicker(time.Second * 1)
	defer ticker.Stop()

	for {
		select {
		case <- ticker.C:
			_, _, sec := time.Now().Clock()
			secs := fmt.Sprintf("%2d", sec)
			if secs > "20" && secs < "40" {
				fmt.Println(secs, "in (20, 40), do nothing")
				break
			}
			fmt.Println("do print secs =", secs)
		}
	}

	time.Sleep(time.Second * 60)
	fmt.Println("ticker stopped")
}