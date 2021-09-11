
package main

import (
	"fmt"
	"reflect"
)

type Student struct {
	name string
	Age int
}

func main() {
	// int 类型
	var a int = 99
	v := reflect.ValueOf(a)
	t := reflect.TypeOf(a)

	fmt.Println(v.Type(), t.Kind(), reflect.ValueOf(&a).Elem())
	fmt.Println(reflect.ValueOf(a).CanSet(), reflect.ValueOf(a).CanAddr())
	fmt.Println(reflect.ValueOf(&a).CanSet(), reflect.ValueOf(&a).CanAddr())

	pa := reflect.ValueOf(&a).Elem()
	fmt.Println("CanSet:", pa.CanSet(), "CanAddr:", pa.CanAddr())
	
	pa.SetInt(100)
	fmt.Println(pa)
	
	// 结构体
	var pupil Student = Student{ "Jim", 8 }
	pupilv := reflect.ValueOf(pupil)
	fmt.Println(pupilv.Type())
	fmt.Println(pupilv.Kind())

	p := reflect.ValueOf(&pupil).Elem()
	fmt.Println("CanSet:", p.CanSet(), "CanAddr:", p.CanAddr())

	// p.Field(0).SetString("Mike")	// name 首字母小写，为不可导出字段，不能修改
	p.Field(1).SetInt(10)
	fmt.Println(p)
}