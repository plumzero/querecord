
package main

import (
	"fmt"
	"os"
	"os/signal"
	"syscall"
)

var ss = make(chan int)

func main() {
	go signalListen()

	select {
	case <- ss:
		fmt.Println("exit")
		break
	}
}

func signalListen() {
	c := make(chan os.Signal)
	signal.Notify(c, syscall.SIGINT, syscall.SIGQUIT)
	for {
		s := <-c
		fmt.Println("get signal:", s)
		ss <- 9
		break
	}
}