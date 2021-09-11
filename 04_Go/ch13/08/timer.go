
package main

import (
	"fmt"
	"time"
)

func main() {
	fmt.Println("begin:", time.Now())

	timer1 := time.NewTimer(time.Second * 2)
	m := <- timer1.C
	fmt.Println("timer1 expired:", m)

	timer2 := time.NewTimer(time.Second * 2)
	go func() {
		<- timer2.C
		fmt.Println("timer2 expired")
	}()
	// timer2 还未到达订时处即停止了
	stop := timer2.Stop()
	if stop {
		fmt.Println(time.Now())
	}
}
