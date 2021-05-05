
package main

import (
	"fmt"
	"strconv"
)

type PersonInfo struct {
	ID string
	Name string
	Address string
}

func SendMap(ch chan map[string]PersonInfo, ssi map[string]PersonInfo) {
	fmt.Println("Send:", ssi)
	ch <- ssi
}

func main() {
	chms := make([]chan map[string]PersonInfo, 10)
	
	for i := 0; i < 10; i++ {
		chms[i] = make(chan map[string]PersonInfo)

		map_sst := make(map[string]PersonInfo, 0)
		for j := 0; j <= i; j++ {
			k := strconv.Itoa(j)
			map_sst[k] = PersonInfo{k, "Robort_" + k,  "Room " + k }
		}

		go SendMap(chms[i], map_sst)
	}

	for _, ch := range(chms) {
		fmt.Println("Received:", <-ch)
	}
}