
package main

import "fmt"

func Counter(out chan<- int) {
	for x := 0; x < 10; x++ {
		out <- x
	}
	close(out)
}

func Squarer(out chan<- int, in <-chan int) {
	for v := range in {
		out <- v * v
	}
	close(out)
}

func Printer(in <-chan int) {
	for v := range in {
		fmt.Println(v)
	}
}

func main() {

	naturals := make(chan int)
	squares := make(chan int)

	go Counter(naturals)
	go Squarer(squares, naturals)
	Printer(squares)
}