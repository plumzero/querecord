
package main

import (
	"fmt"
	"sync"
	"time"
	"os"
	"os/signal"
	"syscall"
)

var wg sync.WaitGroup
var sigmap map[string]chan os.Signal = make(map[string]chan os.Signal, 10)

func AddRoutine(name string) {
	sigmap[name] = make(chan os.Signal, 1)
	signal.Notify(sigmap[name], syscall.SIGTERM, syscall.SIGINT)
	wg.Add(1)
	fmt.Println("would add a routine named", name)

	timeout := make(chan bool, 1)
	go func() {
		for {
			time.Sleep(time.Second)
			timeout <- true
		}
	}()

	go func (name string) {
		defer wg.Done()
		for {
			select {
				case sig := <- sigmap[name]:
					fmt.Println(name, "received signal:", sig)
					goto End	// go case 不需要 break, 但 break 在这里也无法跳出循环，使用 goto
				case <- timeout:
					fmt.Println(name, "is running...")
			}
		}

	End:
		fmt.Println(name, "exit")
	} (name)
}

func DelRoutine(name string) {
	if _, ok := sigmap[name]; ok {
		fmt.Println("would del a routine named", name)
		sigmap[name] <- syscall.SIGTERM
		delete(sigmap, name)
	}
}

func main() {

	AddRoutine("1")
	AddRoutine("2")

	time.Sleep(5 * time.Second)

	DelRoutine("1")

	time.Sleep(3 * time.Second)

	DelRoutine("2")

	wg.Wait()
}