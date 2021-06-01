
package main

import "fmt"

func main() {

	var lang string

	lang = "cpp"

	switch lang {
	case"cpp":
		fmt.Println("c++ language")
	case "java":
		fmt.Println("Java language")
	case "go", "golang":
		fmt.Println("go language");
	default:
		fmt.Println(lang)
	}
}