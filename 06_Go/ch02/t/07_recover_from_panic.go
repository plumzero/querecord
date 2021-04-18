
package main

import (
	"errors"
	"fmt"
)

func DivideForRecover(dividend float64, divisor float64) (result float64) {
	if divisor == 0 {
		err := errors.New("runtime error: divide by zero")
		panic(err)
		return
	}

	return dividend / divisor
}

func main() {
	defer func() {
		if err := recover(); err != nil {
			fmt.Println("panic occured! err info:", err)
		}
	}()

	r := DivideForRecover(6, 0)

	fmt.Println(r)
}