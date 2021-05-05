
package main

import (
	"fmt"
	"time"
)

func main() {
	for i := 0; i < 10; i++ {
		// 匿名函数方式启动协程
		go func(i int) {
			fmt.Println("Hello form goroutine", i)
		}(i)
	}

	time.Sleep(100 * time.Millisecond)
}