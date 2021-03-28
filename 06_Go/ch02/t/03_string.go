
package main

import "fmt"

func main() {
	// 字符串操作
	{
		var str string;

		str = "Hello" + "123"
		fmt.Println(str)

		fmt.Println(len("Hello"))

		c := "Hello"[1]
		fmt.Println(c)
	}

	// 以字节方式遍历
	{
		str := "Hello world"
		n := len(str)
		for i := 0; i < n; i++ {
			ch := str[i]
			fmt.Println(i, ch)  // ch 的类型是 byte
		}
	}

	// 以 Unicode 字符方式遍历
	{
		str := "Hello world"
		for i, ch := range str {
			fmt.Println(i, ch)  // ch 的类型是 rune
		}
	}
}