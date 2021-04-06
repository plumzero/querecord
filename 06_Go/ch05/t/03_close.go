
package main

import (
	"fmt"
)

func Write(ch chan<- int) {
	for i := 0; i < 10; i++ {
		ch <- i
	}
	close(ch)
}

func main() {
	ch := make(chan int)

	go Write(ch)
	
	for {
		v, ok := <- ch
		if ! ok {
			break
		}
		fmt.Println("Parsing value", v)	
	}
}
