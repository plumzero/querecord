
package main

import "fmt"

const (
	Sunday = iota
	Monday
	Tuesday
	Wednesday
	Thursday
	Friday
	Saturday
	numberOfDays
)

func main() {
	fmt.Printf("Sun=%d\n", Sunday)
	fmt.Printf("Sat=%d\n", Saturday)

	// compiled and executed pass, but not recommend do like this
	fmt.Printf("numberOfDays=%d\n", numberOfDays)
}