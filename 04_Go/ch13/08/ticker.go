
package main

import (
	"fmt"
	"time"
)

func main() {
	// 创建一个一个定时器，每秒钟执行一次
	ticker := time.NewTicker(time.Second * 1)
	go func() {
		for t := range ticker.C {
			fmt.Println("tick:", t)
		}
	}()

	time.Sleep(time.Second * 5)
	ticker.Stop()		// 停止定时器
	fmt.Println("ticker stopped")
}