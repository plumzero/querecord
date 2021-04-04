
package main

import (
	"fmt"
	"sync"
)

func Write(wg * sync.WaitGroup, ch chan<- int) {
	defer wg.Done()
	for i := 0; i < 10; i++ {
		ch <- i
	}
	close(ch)
}

func Parse(wg * sync.WaitGroup, ch <-chan int) {
	defer wg.Done()
	for value := range ch {
		fmt.Println("Parsing value", value)
	}
}

func main() {
	ch := make(chan int)

	var wg sync.WaitGroup

	wg.Add(2)
	go Write(&wg, ch)
	go Parse(&wg, ch)

	wg.Wait()
	fmt.Println("All Done!")
}
