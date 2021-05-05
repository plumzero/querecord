
package main

import (
	"fmt"
	"time"
)

func deadlock_routine(ch chan int) {
	fmt.Println(<-ch)
}


func main() {

	ch := make(chan int)
	
	go func() {
		ch <- 1
	} ()

	go deadlock_routine(ch)

	time.Sleep(time.Second)
}