
package main

import (
	"fmt"
	"strings"
)

func main() {
	// Contains
	{
		fmt.Println(strings.Contains("seafood", "foo"))
		fmt.Println(strings.Contains("seafood", "bar"))
		fmt.Println(strings.Contains("seafood", ""))
		fmt.Println(strings.Contains("", ""))
	}

	// ContainsAny
	{
		fmt.Println(strings.ContainsAny("team", "i"))
		fmt.Println(strings.ContainsAny("fail", "ui"))
		fmt.Println(strings.ContainsAny("ure", "ui"))
		fmt.Println(strings.ContainsAny("failure", "ui"))
		fmt.Println(strings.ContainsAny("foo", ""))
		fmt.Println(strings.ContainsAny("", ""))
	}
}
