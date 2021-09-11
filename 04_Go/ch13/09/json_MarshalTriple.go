
package main

import (
	"encoding/json"
	"os"
	"fmt"
)

type DValue struct {
    Triple           [2][2][8]int	`json:"triple"`
    CostTime      	 float64		`json:"costtime"`
}

func main() {
	var dv DValue

	index := 0
	for i := 0; i < len(dv.Triple); i++ {
		for j := 0; j < len(dv.Triple[i]); j++ {
			for k := 0; k < len(dv.Triple[i][j]); k++ {
				index++
				dv.Triple[i][j][k] = index
			}
		}
	}
	dv.CostTime = 3.1415926

	enc := json.NewEncoder(os.Stdout)

	if err := enc.Encode(&dv); err != nil {
		fmt.Println(err)
	}

	b, err := json.Marshal(dv)
	if err != nil {
		panic("Marshal")
	}

	fmt.Println(string(b))

}
