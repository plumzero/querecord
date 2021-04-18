
package main

import (
	"math"
	"fmt"
)

type Shaper interface {
	area() float64
}

type Circle struct {
	radius float64
}

func (c *Circle) area() float64 {
	return math.Pi * c.radius * c.radius
}

func main() {
	circle := Circle{radius: 10}
	var shaperA Shaper

	shaperA = &circle

	var shaperB Shaper
	shaperB = new(Circle)

	fmt.Println("area of Circle A:", shaperA.area())
	fmt.Println("area of Circle B:", shaperB.area())
}