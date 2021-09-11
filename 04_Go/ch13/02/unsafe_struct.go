
package main

import (
	"fmt"
	"unsafe"
)

type V struct {
	i int32
	j int64
}

func (v V) GetI() {
	fmt.Printf("i=%d\n", v.i)
}

func (v V) GetJ() {
	fmt.Printf("j=%d\n", v.j)
}

func main() {
	var v *V = &V{ 199, 299 }

	// 取得 v 的指针并转换为 *int32 的值
	var i *int32 = (*int32)(unsafe.Pointer(v))
	fmt.Println("指针地址:", i)
	fmt.Println("指针 uintptr 值:", uintptr(unsafe.Pointer(i)))
	*i = int32(98)

	// 偏移运算操作成员 j
	var j *int64 = (*int64)(unsafe.Pointer(uintptr(unsafe.Pointer(v)) + uintptr(unsafe.Sizeof(int64(0)))))
	*j = int64(763)

	v.GetI()
	v.GetJ()
}