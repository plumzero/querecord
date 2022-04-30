
package main

import (
	"sort"
	"fmt"
)

type byTime [][]string

func (a byTime) Len() int {
	return len(a)
}

func (a byTime) Less(i, j int) bool {
	return a[i][0] < a[j][0]
}

func (a byTime) Swap(i, j int) {
	a[i], a[j] = a[j], a[i]
}

// code : close
func main() {
	ss := make([][]string, 0)

	ss = append(ss, []string{ "0933", "002345", "19.36" })
	ss = append(ss, []string{ "0931", "002345", "20.56" })
	ss = append(ss, []string{ "0934", "001234", "10.78" })

    sort.Slice(ss, func(i, j int) bool {
		return ss[i][0] < ss[j][0]
	})

	fmt.Printf("len(ss) = %d\n", len(ss))

	for i := 0; i < len(ss); i++ {
		fmt.Printf("%d: %v\n", i, ss[i])
	}
}
