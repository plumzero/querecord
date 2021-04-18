
package main

import (
	"encoding/base64"
	"errors"
	"fmt"
)

func mustDecode(enc *base64.Encoding, str string) string {
	data, err := enc.DecodeString(str)
	if err != nil {
		panic(err)
	}
	
	return string(data)
}

func testEncoding(enc * base64.Encoding, str string) {
	encStr := enc.EncodeToString([]byte(str))
	fmt.Println(encStr)

	decStr := mustDecode(enc, encStr)
	fmt.Println("decStr:", decStr)
	if decStr != str {
		panic(errors.New("unequal!"))
	}
}

func main() {
	const testStr = "Go语言编程"

	testEncoding(base64.StdEncoding, testStr)

	testEncoding(base64.URLEncoding, testStr)

	testEncoding(base64.RawStdEncoding, testStr)

	testEncoding(base64.RawURLEncoding, testStr)
}