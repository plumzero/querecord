
package main

import (
	"strconv"
	"fmt"
)

func main() {
	f, err := strconv.ParseFloat("3.1415", 64)
	if err != nil {
		panic("ParseFloat error")
	}

	var i int32 = int32(f * 10000)

	fmt.Println(i)
}
