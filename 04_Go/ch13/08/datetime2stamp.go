
package main

import (
	"time"
	"fmt"
)

func main() {
	now := time.Now()
	
	year, month, day := now.Date()

	fmt.Println("year =", year, " month =", month, " day =", day)

	closetimestamp := time.Date(year, month, day, 11, 30, 00, 00, time.Local).Unix()

	starttimestamp := time.Date(year, month, day, 13, 00, 00, 00, time.Local).Unix()
	
	fmt.Println("closetimestamp =", closetimestamp, " starttimestamp =", starttimestamp)
}