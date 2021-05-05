
package main

import (
	"math"
	"fmt"
)

type Shaper interface{}

type Circle struct {
	radius float64
}

type Rectangle struct {
	width float64
	length float64
}

func (r Rectangle) getDiagonalLength() float64 {
	return math.Sqrt(r.length * r.length + r.width * r.width)
}

func checkAndProcess(s Shaper) {
	varR, ok := s.(Rectangle)
	if ok {
		fmt.Println(varR.getDiagonalLength())
	} else {
		fmt.Println(varR)
	}
}

func main() {
	var shaperCircle Shaper
	var shaperRect Shaper

	shaperCircle = Circle{5}
	shaperRect = Rectangle{3, 4}

	checkAndProcess(shaperCircle)
	checkAndProcess(shaperRect)
}

