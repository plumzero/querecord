
package main

import (
	"fmt"
	"time"
)

/**
   time.After 源码实现
   func After(d Duration) <-chan Time {
	   return NewTimer(d).C
   }
*/
func main() {
	ch := make(chan int, 1)
	ch <- 1
	for {
		select {
		case e := <- ch:
			fmt.Printf("1th case is selected. e=%v\n", e)
		case <- time.After(time.Second):
			fmt.Println("Time out")
		}
	}
}