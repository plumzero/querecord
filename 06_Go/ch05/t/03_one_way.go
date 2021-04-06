
package main

import (
	"fmt"
	"time"
)

func Write(ch chan<- int) {
	for i := 0; i < 10; i++ {
		ch <- i
	}
}

func Parse(ch <-chan int) {
	for value := range ch {
		fmt.Println("Parsing value", value)
	}
}

func main() {
	ch := make(chan int)

	go Write(ch)
	go Parse(ch)

	time.Sleep(time.Second)
}
