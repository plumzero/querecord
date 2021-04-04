
package main

import (
	"fmt"
	"sync"
)

var wg sync.WaitGroup

type PipeData struct {
	value int
	handler func(int) int
	next chan int
}

func _square(i int) int {
	return i * i
}

func Handle(queue chan *PipeData) {
	defer wg.Done()
	for data := range queue {
		data.next <- data.handler(data.value)
	}
}

func Printer(in <-chan int) {
	defer wg.Done()
	for v := range in {
		fmt.Println(v)
	}
}

func main() {
	
	ch := make(chan *PipeData)
	ch_for_print := make(chan int)	

	wg.Add(2)

	go Printer(ch_for_print)

	go Handle(ch)

	go func() {
		defer wg.Done()
		for i := 0; i < 10; i++ {
			ch <- &PipeData{ i, _square, ch_for_print }
		}
		close(ch)
	}()

	wg.Wait()
}