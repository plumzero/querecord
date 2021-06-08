package main

import (
	"log"
	"strconv"
	"sync"

	"github.com/dullgiulio/pingo"
)

func main() {

	var wg sync.WaitGroup

	wg.Add(2)

	p1 := pingo.NewPlugin("tcp", "plugins/hello/hello")
	p1.Start()
	defer p1.Stop()

	p2 := pingo.NewPlugin("tcp", "plugins/world/world")
	p2.Start()
	defer p2.Stop()

	go func() {
		defer wg.Done()
		var resp string
		for i := 0; i < 10000; i++ {
			if err := p1.Call("MyPlugin.SayHello", "Go plugin one " + strconv.Itoa(i), &resp); err != nil {
				log.Print(err)
			} else {
				log.Print(resp)
			}
		}
	}()

	go func() {
		defer wg.Done()
		var resp string
		for i := 0; i < 10000; i++ {
			if err := p2.Call("MyPlugin.SayWorld", "Go plugin two " + strconv.Itoa(i), &resp); err != nil {
				log.Print(err)
			} else {
				log.Print(resp)
			}
		}
	}()

	wg.Wait()
}
