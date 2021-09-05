
package main

import (
	"fmt"
)

func main() {
	var i int = 1

	// defer 后的函数有两个参数，分别是字符串和匿名函数。它的参数会实时计算，里面的 i 是 1
	// 下面的函数就相当于
	// 	defer func(arg int) { fmt.Println("result1=>", arg * 2) }(i)
	defer fmt.Println("result1=>", func() int { return i * 2 }())
	i++

	// defer 后的函数无参数，也就没有实时计算。在整个 main 函数运行后调用，里面的 i 是 3
	defer func() {
		fmt.Println("result2=>", i * 2)
	} ()
	i++
}