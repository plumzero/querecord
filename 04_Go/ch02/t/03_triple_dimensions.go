
package main

import (
	"errors"
	"fmt"
)

const (
    MarketType_SH    = 1
    MarketType_SZ    = 2
)

const (
    DealType_Buy  =  1
    DealType_Sell = -1
)

const (
    OrderStatus_None           = 0
    OrderStatus_Accepted       = 1
    OrderStatus_TotalMatch     = 2
    OrderStatus_PartialRemoved = 3
    OrderStatus_TotalRemoved   = 4
    OrderStatus_Fail           = 5
    OrderStatus_Removing       = 6
    OrderStatus_Pending        = 7
    OrderStatus_PartialMatch   = 8
)

// M D O
var triple [2][2][8]int

func init() {
	for i := 0; i < len(triple); i++ {
		for j := 0; j < len(triple[i]); j++ {
			for k := 0; k < len(triple[i][j]); k++ {
				triple[i][j][k] = 0
			}
		}
	}
}

func check(market, dealtype, orderstatus int) error {
	if market != MarketType_SH && market != MarketType_SZ {
		return errors.New("market type illegal")
	}

	if dealtype != DealType_Buy && dealtype != DealType_Sell {
		return errors.New("deal type illegal")
	}

	if orderstatus < 1 || orderstatus > 8 {
		return errors.New("order status illegal")
	}

	return nil
}

func index(m, d, o int) (i, j, k int) {
    if err := check(m, d, o); err != nil {
        return -1, -1, -1
    }

    i, j, k = 0, 0, 0

	i = m - MarketType_SH
	if d == DealType_Buy {
		j = 0
	} else {
		j = 1
	}
	k = o - 1

    return i, j, k
}

func addto(market, dealtype, orderstatus int) error {
	if err := check(market, dealtype, orderstatus); err != nil {
		return err
	}

	i, j, k := index(market, dealtype, orderstatus)

	triple[i][j][k] += 1

	return nil
}

func fetch(market, dealtype, orderstatus int) int {
	if err := check(market, dealtype, orderstatus); err != nil {
		return -1
	}

	i, j, k := index(market, dealtype, orderstatus)

	return triple[i][j][k]
}

func print() {
	for i := 0; i < len(triple); i++ {
		for j := 0; j < len(triple[i]); j++ {
			for k := 0; k < len(triple[i][j]); k++ {
				fmt.Printf("%2d ", triple[i][j][k])
			}
			fmt.Printf(" | ")
		}
		fmt.Printf("\n")
	}
}

func main() {

	for i := 0; i < 30; i++ {
		addto(MarketType_SH, DealType_Buy, OrderStatus_TotalRemoved)
	}

	for i := 0; i < 14; i++ {
		addto(MarketType_SH, DealType_Sell, OrderStatus_TotalRemoved)
	}

	for i := 0; i < 23; i++ {
		addto(MarketType_SZ, DealType_Buy, OrderStatus_TotalRemoved)
	}

	for i := 0; i < 8; i++ {
		addto(MarketType_SZ, DealType_Buy, OrderStatus_TotalMatch)
	}

	for i := 0; i < 11; i++ {
		addto(MarketType_SH, DealType_Buy, OrderStatus_TotalMatch)
	}

	for i := 0; i < 9; i++ {
		addto(MarketType_SH, DealType_Sell, OrderStatus_TotalMatch)
	}

	for i := 0; i < 2; i++ {
		addto(MarketType_SZ, DealType_Sell, OrderStatus_TotalMatch)
	}

	for i := 0; i < 15; i++ {
		addto(MarketType_SZ, DealType_Sell, OrderStatus_TotalRemoved)
	}

	print()
}