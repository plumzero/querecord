
package main

import (
	"encoding/json"
	"os"
	"strings"
	"fmt"
)

func main() {

	b := []byte(
		`{
			"Title": "Golang programing",
			"Authors": [ "XuShiWei", "HughLv", "Pandaman", "GuaguaSong" ],
			"Publisher": "ituring.com.cn",
			"IsPublished": true,
			"Price": 9.99
		}`,
	)

	dec := json.NewDecoder(strings.NewReader(string(b)))
	enc := json.NewEncoder(os.Stdout)

	for {
		var v map[string]interface{}
		if err := dec.Decode(&v); err != nil {
			fmt.Println(err)
			return
		}

		if err := enc.Encode(&v); err != nil {
			fmt.Println(err)
		}
	}
}
