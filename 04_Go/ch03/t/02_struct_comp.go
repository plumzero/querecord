
package main

import (
	"fmt"
)

func main() {
	type Student struct {
		ID int
		Name string
		Address string
		Age int
		Class string
		Teacher string
	}

	s1 := Student{20210418, "LiMing", "ShangHai", 18, "CS&T", "Yang"}
	s2 := Student{20210418, "LiMing", "ShangHai", 18, "CS&T", "Yang"}
	s3 := Student{20210423, "LiMing", "ShangHai", 18, "CS&T", "Yang"}

	fmt.Println("s1 == s2?", s1 == s2)
	fmt.Println("s1 == s3?", s1 == s3)

	var tmp Student
	tmp = s3
	fmt.Println("tmp =", tmp)
}