
package main

import (
	"fmt"
	"strings"
	"unicode"
)

func main() {
	// Fields
	{
		var str string = "  foo bar  baz	";
		vecstrs := strings.Fields(str)

		for i,v := range vecstrs {
			fmt.Printf("|i=%d,v=%s|", i, v)
		}
		fmt.Println()
	}

	// FieldsFunc
	{
		str := "  foo1;bar2,baz3...";
		vecstrs := strings.FieldsFunc(str, func(c rune) bool {
			return ! unicode.IsLetter(c) && ! unicode.IsNumber(c)
		})

		for i,v := range vecstrs {
			fmt.Printf("|i=%d,v=%s|", i, v)
		}
		fmt.Println()
	}
}
