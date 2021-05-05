
package main

// 以下注释中的 C 代码与下面的 import "C" 语句必须紧紧挨着

/*
#include <stdio.h>
#include <stdlib.h>
*/
import "C"

import "unsafe"

func main() {
	cstr := C.CString("Hello World")
	C.puts(cstr)						// C function puts in stdio
	C.free(unsafe.Pointer(cstr))		// C function free in stdlib
}