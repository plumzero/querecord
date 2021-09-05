
package main

import (
	"fmt"
)

type Writer interface {
	Write()
}

type Author struct {
	name string
	Writer
}

type Other struct {
	i int
}

func (a Author) Write() {
	fmt.Println(a.name, " Write.")
}

// 结构体 Oter 实现了接口方法 Write()，也就可以在 Author 初始化时赋值给 Writer 接口
func (o Other) Write() {
	fmt.Println("Other Write.")
}

func main() {
	// 方法一: Other{99} 作为 Writer 接口赋值
	Ao := Author{ "Other", Other{99} }
	Ao.Write()

	// 方法二: 简易写法，对接口使用零值，可以完成初始化
	Au := Author{ name: "Hawking" }
	Au.Write()
}