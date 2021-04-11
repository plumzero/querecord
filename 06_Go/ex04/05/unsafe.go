
package main

import (
	"fmt"
	"unsafe"
)

func main() {
    var i32 int32 = 10
    var p32 *int32 = &i32
    var p64 *int64 = (*int64)(unsafe.Pointer(p32))
    var i64 int64 = *p64
	
	fmt.Println(i64)
}