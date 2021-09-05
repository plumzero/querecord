
package main

import (
	"fmt"
)

type People struct {
	Name string
}

type OtherPeople struct {
	People
	Name string
}

func (p People) PeInfo() {
	fmt.Println("People Name:", p.Name)
}

func main() {
	op := OtherPeople{ Name: "outer_name", People: People{ Name: "inner_name" } }

	op.People.PeInfo()

	op.PeInfo()
}