
package main

import (
	"fmt"
	"sync"
	"time"
)

func onceFunc() {
	fmt.Println("Only once")
}

func main() {
	var once sync.Once

	for i := 0; i < 10; i++ {
		j := i
		go func(int) {
			once.Do(onceFunc)
			fmt.Println(j)
		}(j)
	}

	time.Sleep(time.Second * 1)
}