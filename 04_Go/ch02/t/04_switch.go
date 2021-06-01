
package main

import "fmt"

func main() {
	for _, v := range [...]int{1, 2, 4, 8} {
		switch v {
            case 0:
                fmt.Println("Zero")
            case 1:
                fmt.Println("One")
            case 2:
                fallthrough
            case 3:
                fmt.Println("Two, Three")
            case 4, 5, 6:
                fmt.Println("Four, Five, Six")
            default:
                fmt.Println("Default")
    	}
	}
}