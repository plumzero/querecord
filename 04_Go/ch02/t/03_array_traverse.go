
package main

import "fmt"

func main() {

	array := [5]int{ 10, 20, 30, 40, 50 }

	for i := 0; i < len(array); i++ {
		fmt.Println("Element", i , "of array is", array[i])
	}

	for i, v := range array {
		fmt.Println("Array element[", i, "]=", v)
	}
}