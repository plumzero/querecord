
package main

import (
	"fmt"
	"sort"
)

type River struct {
	Name string
	Length int
}

func main() {
	rivers := []River {
		{"刚果河", 4640},
		{"尼罗河", 6670},
		{"亚马逊河", 6400},
		{"黄河", 5464},
		{"鄂毕河", 3650},
		{"恒河", 2510},
		{"密西西比河", 6021},
		{"叶尼塞河", 5539},
		{"长江", 6300},
	}

	sort.Slice(rivers, func(i, j int) bool {
		return rivers[i].Length >= rivers[j].Length
	})

	fmt.Println(rivers)
}