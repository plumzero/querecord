
package main

import (
	"sort"
	"fmt"
)

type Student struct {
	Name string
	Age int
	Score float64
}

type StudentList []Student

func NewList(list []Student) *StudentList {
	var slist StudentList
	for _, stu := range list {
		slist = append(slist, stu)
	}
	return &slist
}

func (slist StudentList) Len() int {
	return len(slist)
}

func (slist StudentList) Less(i, j int) bool {
	return slist[i].Score < slist[j].Score
}

func (slist StudentList) Swap(i, j int) {
	slist[i], slist[j] = slist[j], slist[i]
}

func main() {
	stu1 := Student{ "funny", 18, 91.32 }
	stu2 := Student{ "jerry", 20, 88.43 }
	stu3 := Student{ "curry", 20, 89.56 }
	stu4 := Student{ "james", 19, 93.00 }

	list := []Student{ stu1, stu2, stu3, stu4 }

	sl := NewList(list)

	sort.Sort(sl)

	fmt.Println(sl)
}