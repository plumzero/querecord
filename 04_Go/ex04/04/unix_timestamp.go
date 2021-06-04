
package main

import (
	"time"
	"strconv"
	"fmt"
)

// bt = "0930",  et = "1505"
func TimeInInterval(bt, et string) []string {
	var bh, bm, eh, em int
	if len(bt) == 0 {
		bh = 9
		bm = 30
	} else {
		bh, _ = strconv.Atoi(bt[:2])
		bm, _ = strconv.Atoi(bt[2:])
	}
	if len(et) == 0 {
		eh = 15
		em = 05
	} else {
		eh, _ = strconv.Atoi(et[:2])
		em, _ = strconv.Atoi(et[2:])
	}

	b := time.Date(2004, time.January, 1, bh, bm, 0, 0, time.Local)
	e := time.Date(2004, time.January, 1, eh, em, 0, 0, time.Local)

	buts := b.Unix()
	euts := e.Unix()

	hms := []string{}
	for tp := buts; tp <= euts; tp += 60 {
		hour, min, _ := time.Unix(tp, 0).Clock()
		hms = append(hms, fmt.Sprintf("%02d%02d", hour, min))
	}

	return hms
}

func main() {
	b := time.Date(2004, time.January, 1,  9, 30, 0, 0, time.Local)		// 本地的 Unix 时间戳
	e := time.Date(2004, time.January, 1, 15,  5, 0, 0, time.Local)

	buts := b.Unix()
	euts := e.Unix()

	bhour, bmin, bsec := time.Unix(buts, 0).Clock()
	ehour, emin, esec := time.Unix(euts, 0).Clock()

	fmt.Printf("b(uts=%d, hour=%d, min=%d, sec=%d)\n", buts, bhour, bmin, bsec)
	fmt.Printf("e(uts=%d, hour=%d, min=%d, sec=%d)\n", euts, ehour, emin, esec)

	hms := []string{}
	for tp := buts; tp <= euts; tp += 60 {
		hour, min, _ := time.Unix(tp, 0).Clock()
		hms = append(hms, fmt.Sprintf("%02d%02d", hour, min))
	}
	fmt.Println("len(hms) =", len(hms))

	for i, v := range hms {
		fmt.Printf("%s ", v)
		if (i + 1) % 30 == 0 {
			fmt.Printf("\n")
		}
	}
	fmt.Printf("\n")
	fmt.Println("---------------------------------------------------------------------")

	xhms := TimeInInterval("", "1505")
	for i, v := range xhms {
		fmt.Printf("%s ", v)
		if (i + 1) % 30 == 0 {
			fmt.Printf("\n")
		}
	}
	fmt.Printf("\n")
}