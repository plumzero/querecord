
package main

import (
	"fmt"
	"reflect"
)

type Student struct {
	name string
}

type MyInt int

type IntAlias = int

func main() {
	// 内建类型
	var a int = 9
	v := reflect.ValueOf(a)
	t := reflect.TypeOf(a)
	fmt.Println(v, t, v.Type(), v.Kind(), t.Kind())

	// 自定义类型
	var mi MyInt = 99
	mv := reflect.ValueOf(mi)
	mt := reflect.TypeOf(mi)
	fmt.Println(mv, mt, mv.Type(), mv.Kind(), mt.Kind())

	// 类型别名
	var ia IntAlias = 999
	iv := reflect.ValueOf(ia)
	it := reflect.TypeOf(ia)
	fmt.Println(iv, it, iv.Type(), iv.Kind(), it.Kind())

	// 数组
	var b [5]int = [5]int{ 5, 6, 7, 8 }
	fmt.Println(reflect.TypeOf(b), reflect.TypeOf(b).Kind(), reflect.TypeOf(b).Elem())

	var pupil Student
	p := reflect.ValueOf(pupil)
	fmt.Println(p.Type(), p.Kind())
}