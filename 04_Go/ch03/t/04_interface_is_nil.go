
package main

import (
	"fmt"
)

func readcb()(out interface{}, err error) {
	return
}

func writecb(in interface{})(err error) {
	return
}

func test(rcb func()(interface{}, error), wcb func(interface{})(error)) {
	if (rcb == nil) {
		fmt.Println("read callback is nil")
	}
	if (wcb == nil) {
		fmt.Println("write callback is nil")
	}
}

func main() {

	test(nil, nil)

	test(nil, writecb)

	test(readcb, nil)
}