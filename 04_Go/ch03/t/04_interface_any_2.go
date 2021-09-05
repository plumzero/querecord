
package main

import (
	"fmt"
)

type Any interface{}

type Rectangle struct {
	width float64
	length float64
}

type Shaper interface {
	area() float64
}

func (r *Rectangle) area() float64 {
	return r.width * r.length
}

func main() {
	var any Any
	var rect Rectangle = Rectangle{10, 10}
	var shaper Shaper

	any = rect
	fmt.Println("Any has the value", any)

	any = &rect
	fmt.Println("Any has the value", any)

	any = shaper
	fmt.Println("Any has the value", any)

	shaper = &rect
	any = shaper
	fmt.Println("Any has the value", any)

	any = 42
	fmt.Println("Any has the value", any)

	any = "everything"
	fmt.Println("Any has the value", any)
}