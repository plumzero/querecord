
package main

import (
	"time"
	"fmt"
)

func main() {

	fmt.Println("date time:", time.Now().Format("2006-01-02 15:04:05"))
	fmt.Println("date only:", time.Now().Format("2006-01-02"))
	fmt.Println("time only:", time.Now().Format("15:04:05"))
	fmt.Println("date time:", time.Now().Format("20060102"))

	fmt.Println("hour only:", time.Now().Hour())
	fmt.Println("minute only:", time.Now().Minute())
	fmt.Println("second only:", time.Now().Second())
}