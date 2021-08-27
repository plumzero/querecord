
package main

import (
	"fmt"
	"reflect"
)

type Student struct {
	name string "学生名字"
	Age  int    "学生年龄"
	Room int    `json:"Roomid"`
}

func main() {
	st := Student{ "Titan", 14, 102 }
	fmt.Println(reflect.TypeOf(st).Field(0).Tag)
	fmt.Println(reflect.TypeOf(st).Field(1).Tag)
	fmt.Println(reflect.TypeOf(st).Field(2).Tag)
}