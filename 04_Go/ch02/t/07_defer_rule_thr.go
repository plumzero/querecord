
package main

import (
	"fmt"
)

func func1() (i int) {	// func1 的返回值是有名的，名字为 i。如果只是单纯的写为 int，那么就是无名的返回值，规则三便不再适用
	defer func() {
		i = i + 10	// defer 可以读取有名返回值
	} ()

	return 0	// func1 返回 10 而不是 0
}

func main() {
	fmt.Println("result1 =>", func1())
}