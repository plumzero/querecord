
package main

import (
	"fmt"
	"sort"
)

type person struct {
	Name string
	Age int
}

type personSlice []person

func (s personSlice) Len() int { return len(s) }
func (s personSlice) Swap(i, j int) { s[i], s[j] = s[j], s[i] }
func (s personSlice) Less(i, j int) bool { return s[i].Age < s[j].Age }

func main() {
	a := personSlice {
		{ Name: "Jim", Age: 15 },
		{ Name: "Tom", Age: 57 },
		{ Name: "Sam", Age: 33 },
	}

	sort.Sort(a)
	fmt.Println("Sort:", a)

	sort.Stable(a)
	fmt.Println("Stable:", a)
}