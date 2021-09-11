
package main

import (
	"fmt"
	"reflect"
)

func main() {
	// 反射创建 int 变量
	t := 9
	varType := reflect.TypeOf(t)

	v1 := reflect.New(varType)
	v1.Elem().SetInt(1)
	varNew := v1.Elem().Interface()
	fmt.Printf("int Var: 指针: %d 值: %d\n", v1, varNew)

	// 反射创建 map slice
	newSlice := make([]int, 5)
	newMap := make(map[string]int)
	sliceType := reflect.TypeOf(newSlice)
	mapType := reflect.TypeOf(newMap)

	ReflectSlice := reflect.MakeSlice(sliceType, 5, 5)
	ReflectMap := reflect.MakeMap(mapType)

	V := 99
	SliceV := reflect.ValueOf(V)
	ReflectSlice = reflect.Append(ReflectSlice, SliceV)
	intSlice := ReflectSlice.Interface().([]int)
	fmt.Println("Slice:", intSlice)

	Key := "Rose"
	Value := 999
	MapKey := reflect.ValueOf(Key)
	MapValue := reflect.ValueOf(Value)
	ReflectMap.SetMapIndex(MapKey, MapValue)
	mapStringInt := ReflectMap.Interface().(map[string]int)
	fmt.Println("Map:", mapStringInt)
}