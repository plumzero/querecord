
package main

import (
	"errors"
	"fmt"
)

func DivideTest(dividend float64, divisor float64) (result float64, err error) {
	if divisor == 0 {
		result = 0.0
		err = errors.New("runtime error: divide by zero")
		return
	}

	return dividend / divisor, nil
}

func main() {
	r, err := DivideTest(6.6, 0)
	if err != nil {
		fmt.Println(err)
	} else {
		fmt.Println(r)
	}
}