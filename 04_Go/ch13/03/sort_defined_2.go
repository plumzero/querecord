
package main

import (
	"sort"
	"fmt"
)

type GrpcServer struct {
    Name        string
    Addr        string
    Receivers   []string
    Weight      int
}

type ByWeight []GrpcServer

func (a ByWeight) Len() int {
	return len(a)
}

func (a ByWeight) Less(i, j int) bool {
	return a[i].Weight < a[j].Weight
}

func (a ByWeight) Swap(i, j int) {
	a[i], a[j] = a[j], a[i]
}

func (a ByWeight) Search(name string) int {
	for pos, ele := range a {
		if ele.Name == name {
			return pos
		}
	}

	return -1
}

func main() {
	s1 := GrpcServer{ Name: "caitong", Addr: "127.0.0.1:12345", Receivers: []string{ "redis-LimitedPriceData-real" }, Weight: 1800 }
	s2 := GrpcServer{ Name: "gwt-sz2", Addr: "121.0.0.1:23456", Receivers: []string{ "redis-LimitedPriceData-real" }, Weight: 700 }
	s3 := GrpcServer{ Name: "gwt-sh",  Addr: "127.0.0.1:45678", Receivers: []string{ "redis-LimitedPriceData-real" }, Weight: 500 }
	s4 := GrpcServer{ Name: "zhongjian", Addr: "127.0.0.1:11223", Receivers: []string{ "redis-LimitedPriceData-real" }, Weight: 400 }
	s5 := GrpcServer{ Name: "gwt-sh", Addr: "127.0.0.1:22334", Receivers: []string{ "redis-LimitedPriceData-real" }, Weight: 300 }
	s6 := GrpcServer{ Name: "idc", Addr: "127.0.0.1:33445", Receivers: []string{ "redis-LimitedPriceData-real" }, Weight: 200 }

	ss := ByWeight{ s5, s3, s2, s6, s1, s4 }

	for _, e := range ss {
		fmt.Println(e)
	}

	sort.Sort(ss)
	for _, e := range ss {
		fmt.Println(e)
	}
}