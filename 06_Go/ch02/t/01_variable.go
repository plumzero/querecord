
package main

import "fmt"

func GetName()(firstName, lastName, nickName string) {
	return "May", "Chan", "Chibi Maruko"
}

func main() {
	_,_,nickName := GetName()
	fmt.Printf("nickName=%s\n", nickName)
}