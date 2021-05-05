
package main

import "fmt"

func main() {
	// 值语义
	{
		var a = [3]int{ 1, 2, 3 }
		var b = a
		b[1]++
		fmt.Println(a, b)
	}

	// 利用指针表达引用
	{
		var a = [3]int{ 1, 2, 3 }
		var b = &a
		b[1]++
		fmt.Println(a, *b)
	}

}