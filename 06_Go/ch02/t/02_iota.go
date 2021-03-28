
package main

import "fmt"

func main() {

	const (			// 第一个 const 出现，置 0
		c0 = iota
		c1 = iota
		c2 = iota
	)
	fmt.Printf("c0=%d c1=%d c2=%d\n", c0, c1, c2)

	const (			// 再次出现，置 0
		a = 1 << iota
		b = 1 << iota
		c = 1 << iota
	)
	fmt.Printf("a=%d b=%d c=%d\n", a, b, c)

	const (
		u         = iota * 42
		v float64 = iota * 42
		w         = iota * 42
	)
	fmt.Printf("u=%d v=%f w=%d\n", u, v, w)

	const x = iota
	const y = iota
	fmt.Printf("x=%d y=%d\n", x, y)
}