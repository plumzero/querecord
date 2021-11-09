
package main

import (
	lls "github.com/emirpasic/gods/stacks/linkedliststack"
	"fmt"
)

type MyStruct struct {
	i int32
}

func main() {
	stack := lls.New()
	stack.Push(&MyStruct{i: 10})
	stack.Push(&MyStruct{i: 20})
	stack.Values()
	x, bl := stack.Pop()
	if bl {
		fmt.Println(x.(*MyStruct).i, bl)
	}
	x, bl = stack.Pop()
	if bl {
		fmt.Println(x.(*MyStruct).i, bl)
	}
	x, bl = stack.Pop()
	if bl {
		fmt.Println(x.(*MyStruct).i, bl)
	}
	stack.Push(&MyStruct{i: 30})
	stack.Clear()
	stack.Empty()
	fmt.Println(stack.Size())
}