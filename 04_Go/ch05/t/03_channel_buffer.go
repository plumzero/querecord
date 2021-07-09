
package main

import (
	"fmt"
)

func main() {
	ch := make(chan interface{}, 1)
	
	select {
		case ch <- "10":		// 可以被写入，因为此处 ch 是空的
		default:
	}

	select {
		case ch <- "11":		// 不可以被写入，缓冲区已满
	default:
		fmt.Println(<-ch)		// 10
	}
}