
package main

import (
	"fmt"
	"time"
)

func routine(ch chan int) {
	fmt.Println("channel address in routine:", ch)
	fmt.Println(<-ch)
}


func main() {

	ch := make(chan int)
	
	fmt.Println("channel address after created:", ch)

	go func() {
		fmt.Println("channel address in anonymous function:", ch)
		ch <- 1
	} ()

	go routine(ch)

	var chmap map[string]chan int
	chmap = make(map[string]chan int, 1)

	chmap["first"] = ch
	fmt.Println("channel address in map:", chmap["first"])

	time.Sleep(time.Second)
}