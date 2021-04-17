
package main

import (
	"fmt"
)

func test() func() int {
	x := 3
	return func() int {
		x++
		return x
	}
}

func main() {
	x := test()
	fmt.Println("x =", x())
}