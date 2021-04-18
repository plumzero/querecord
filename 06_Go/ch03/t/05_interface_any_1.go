
package main

import "fmt"

func PrintArgs(args ...interface{}) {
	for _, v := range args {
		switch v.(type) {
			case int:
				fmt.Println("type -> int, val ->", v)
			case string:
				fmt.Println("type -> string, val ->", v)
			default:
				fmt.Println("type -> other type, val ->", v)
		}
	}
}


func main() {

    var v1 interface{} = 123        // 将 int 类型赋值给 interface{}
    var v2 interface{} = "abc"      // 将 string 类型赋值给 interface{}
    var v3 interface{} = &v2        // 将 *interface{} 类型赋值给 interface{}
    var v4 interface{} = struct{ X int }{1}
    var v5 interface{} = &struct { X int }{1}

	PrintArgs(v1, v2, v3, v4, v5)
}