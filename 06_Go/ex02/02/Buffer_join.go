
package main

import (
	"fmt"
	"bytes"
)

func main() {
	var buf bytes.Buffer
	n, err := buf.WriteString("abcd")
	if err == nil {
		fmt.Println("n=", n)
		fmt.Println("buf=", buf.String())
	} else {
		fmt.Println(err.Error())
	}

	buf.WriteString("efgh")
	fmt.Println("buf=", buf.String())
}