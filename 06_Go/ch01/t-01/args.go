
package main

import (
	"fmt"
	"os"
)

func main() {
	fmt.Printf("total %d parameter(s)\n", len(os.Args))

	for idx, args := range os.Args {
		fmt.Printf("parameter: %d : %s\n", idx, args)
	}
}