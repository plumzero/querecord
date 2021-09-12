
package main

import (
	"strings"
	"fmt"
)

func main() {
	s := []string{ "foo", "bar", "baz" }
	fmt.Println(strings.Join(s, ","))
}