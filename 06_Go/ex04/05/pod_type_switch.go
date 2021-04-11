
package main

import (
	"fmt"
)

func main() {

	// 内置函数转换
	{
		var a float32 = 5.6
		var b int = 10

		// fmt.Println(a * b)	// compiled error
		fmt.Println(a * float32(b))
	}

}