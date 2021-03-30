
package main

import "fmt"

func main() {

	{
		var i int = 12

		if i++; i % 2 == 0 {
			fmt.Println(i, "is an even")
		} else {
			fmt.Println(i, "is an odd")
		}
	}

}