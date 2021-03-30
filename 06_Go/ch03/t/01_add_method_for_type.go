
package main

import "fmt"

type Integer int
    
func (a Integer) Less(b Integer) bool {
	return a < b
}

func (a *Integer) Add(b Integer) {
	*a += b
}

func main() {
	{
		var a Integer = 1
		if a.Less(2) {
			fmt.Println(a, "is less than 2")
		}
	}

	{
        var a Integer = 1
        a.Add(2)
        fmt.Println("a =", a)
	}
}
