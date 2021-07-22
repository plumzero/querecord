
package main

import (
	"fmt"
)

func main() {
	var counter int = 8
	
	strs := []string{
		"a",
		"b",
		"c",
		"d",
		"e",
		"f",
		"g",
		"h",
		"i",
		"j",
		"k",
		"m",
		"n",
	}

	strs_len := len(strs)
	fmt.Println("res = ", counter * 100 / strs_len)
}