
package main

import "fmt"

// 定义 Stringer 接口
type Stringer interface {
	String() string		// 名字为 String, 无入参，返回值为 string 的函数
}

// 定义类
type MyString struct {
}
// 定义类方法(实现接口)
func (str MyString) String() string {
	return "UltraBoy"
}

func MyPrintln(args ...interface{}) {
	for _, v1 := range args {
		switch v1.(type) {
			case int:
				fmt.Println("-> int")
			case string:
				fmt.Println("-> string")
			default:
				// 断言 v1 指向的对象是否是 Stringer 类型
				if v,ok := v1.(Stringer); ok {
					val := v.String()
					fmt.Println("->", val)
				} else {
					fmt.Println("pointed to nothing")
				}
		}
	}
}

func main() {
	var ser Stringer
	var ms1 Stringer = new(MyString)
	var ms2 MyString

	MyPrintln("Hello", 123, "World", ser, ms1, ms2)
}