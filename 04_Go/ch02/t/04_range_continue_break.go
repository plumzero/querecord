
package main

import (
	"fmt"
)

func main() {
	array := []int{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 }

	for _, val := range array {
		if val % 2 == 0 {
			continue
		}

		if val == 9 {
			break
		}

		fmt.Println(val)
	}
}