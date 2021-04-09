
package main

import (
	"fmt"
	"sync"
	"time"
)

type MonsterCard struct {
	name   string
	race   string
	atk	   int
	def    int
}

type MagicCard struct {
	name   string
	kind   string
}

type TrapCard struct {
	name   string
	kind   string
}

func main() {

	monster := MonsterCard{ "Madolche Queen Tiaramisu", "angel", 2200, 2100 }
	magic := MagicCard{ "Madolche Chateau",  "field" }
	trap := TrapCard{ "Madolche Lesson", "once" }

	// fmt.Println(monster)
	// fmt.Println(magic)
	// fmt.Println(trap)

	var wg sync.WaitGroup

	ch := make(chan interface{}, 16)

	wg.Add(1)
	go func(wg * sync.WaitGroup) {
		defer wg.Done()
		fmt.Println(<- ch)
		fmt.Println(<- ch)
		fmt.Println(<- ch)
	} (&wg)

	ch <- &monster

	time.Sleep(1 * time.Second)
	ch <- &magic
	
	time.Sleep(1 * time.Second)
	ch <- &trap
	
	wg.Wait()
}