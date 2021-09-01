
package main

import (
	"fmt"
)

type Writer interface {
	Write()
}

type Author struct {
	name string
	Writer
}

type Other struct {
	i int
}

func (a Author) Write() {
	fmt.Println(a.name, " Write.")
}

func (o Other) Write() {
	fmt.Println("Other Write.")
}

func main() {
	
}