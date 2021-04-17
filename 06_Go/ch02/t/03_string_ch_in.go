
package main

import "fmt"

func main() {
	str := "中华人民共和国"

	chstr := []rune(str)
	
	for i := 0; i < len(chstr); i++ {
		fmt.Printf("[%d] = %c\n", i, chstr[i])
	}
}