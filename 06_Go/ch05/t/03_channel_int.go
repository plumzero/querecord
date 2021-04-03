
package main

import "fmt"

func Send(ch chan int, i int) {
	fmt.Println("Sent:", i)
	ch <- i
}

func main() {
	chs := make([]chan int, 10)
	
	for i := 0; i < 10; i++ {
		chs[i] = make(chan int)
		go Send(chs[i], i)
	}

	for _, ch := range(chs) {
		fmt.Println("Received:", <-ch)
	}
}
