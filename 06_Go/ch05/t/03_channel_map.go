
package main

import (
	"fmt"
	"strconv"
)

func SendMap(ch chan map[string] int, si map[string] int) {
	fmt.Println("Send:", si)
	ch <- si
}

func main() {
	chms := make([]chan map[string] int, 10)
	
	for i := 0; i < 10; i++ {
		chms[i] = make(chan map[string] int)

		map_si := make(map[string]int, 0)
		for j := 0; j <= i; j++ {
			k := strconv.Itoa(j)
			map_si[k] = j
		}

		go SendMap(chms[i], map_si)
	}

	for _, ch := range(chms) {
		fmt.Println("Received:", <-ch)
	}
}