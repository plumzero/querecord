
package main

import (
	"fmt"
	"sync"
	"time"
)

var locker = new(sync.Mutex)
var cond = sync.NewCond(locker)
var wt sync.WaitGroup

func test(x int) {
	cond.L.Lock()
	fmt.Println("go routine had been locked")
	cond.Wait()

	fmt.Println("go routine", x, "been notified to execute continuelly...")

	time.Sleep(time.Second)
	
	defer func() {
		cond.L.Unlock()
		wt.Done()
	}()
}

func main() {
	for i := 0; i < 10; i++ {
		go test(i)
		wt.Add(1)
	}

	fmt.Println("start all")
	
	time.Sleep(time.Second * 1)
	cond.Signal()

	time.Sleep(time.Second * 1)
	cond.Signal()

	time.Sleep(time.Second * 1)
	cond.Broadcast()

	wt.Wait()
}