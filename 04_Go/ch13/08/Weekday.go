
package main

import (
	"time"
	"fmt"
)

func main() {
	switch time.Now().Weekday() {
	case time.Saturday:
		fmt.Println("今天是周六")
	case time.Sunday:
		fmt.Println("今天是周末")
	case time.Monday:
		fmt.Println("今天是周一")
	case time.Tuesday:
		fmt.Println("今天是周二")
	case time.Wednesday:
		fmt.Println("今天是周三")
	case time.Thursday:
		fmt.Println("今天是周四")
	case time.Friday:
		fmt.Println("今天是周五")
	}
}