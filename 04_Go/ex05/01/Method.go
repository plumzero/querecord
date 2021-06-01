package main

import (
	"fmt"
	"reflect"
)

type FunctionsMapType map[string]reflect.Value

type MyStruct struct {
	str string
}

func (this *MyStruct) Unchanged(msg string) {
	fmt.Println("Unchanged:", msg)
}

func (this *MyStruct) ChangeParameter(msg *string) {
	*msg = *msg + " Changed"
}

func (this *MyStruct) ChangeMember() {
	this.str = "Hello World"
}

func main() {
	var ms MyStruct

	fmap := make(FunctionsMapType, 0)

	//创建反射变量，注意这里需要传入ruTest变量的地址；
	//不传入地址就只能反射Routers静态定义的方法
	vf := reflect.ValueOf(&ms)
	vft := vf.Type()

	//读取方法数量
	mNum := vf.NumMethod()
	fmt.Println("NumMethod:", mNum)
	//遍历方法，并将其存入映射变量中
	for i := 0; i < mNum; i++ {
		mName := vft.Method(i).Name
		fmt.Println("index:", i, " MethodName:", mName)
		fmap[mName] = vf.Method(i)
	}

	//演示
	testStr := "Hello Go"
	//创建带调用方法时需要传入的参数列表
	parms := []reflect.Value{reflect.ValueOf(testStr)}
	//使用方法名字符串调用指定方法
	fmap["Unchanged"].Call(parms)

	//创建带调用方法时需要传入的参数列表
	parms = []reflect.Value{reflect.ValueOf(&testStr)}
	fmap["ChangeParameter"].Call(parms)
	fmt.Println("testStr:", testStr)

	fmap["ChangeMember"].Call(nil)
	fmt.Println("ms.str:", ms.str)
}