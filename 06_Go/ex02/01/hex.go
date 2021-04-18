
package main

import (
	"encoding/hex"
	"fmt"
)

func main() {
	src := []byte("Hello Go!")
	fmt.Println("source len:", len(src))

	dst := make([]byte, hex.EncodedLen(len(src)))
	fmt.Println("dst len:", len(dst))

	hex.Encode(dst, src)
	fmt.Println("encoded:", string(dst))

	src2 := []byte("48656c6c6f20476f21")
	dst2 := make([]byte, hex.DecodedLen(len(src2)))
	_, err := hex.Decode(dst2, src2)
	if err != nil {
		panic(err)
	}
	fmt.Println("encoded:", string(dst2))
}