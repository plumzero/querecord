
package main

import (
	"fmt"
	"encoding/json"
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

	var r interface{}

	err := json.Unmarshal(b, &r)
	if err != nil {
		panic(err)
	}

	// 执行解码后，JSON 对象会被解码到空接口 r 中，最终 r 将会是一个
	// 键值对的 map[string]interface{} 结构，如下
	/*
		map[string]interface{} {
			"Title" : "Golang programing",
			"Authors" : [ "XuShiWei", "HughLv", "Pandaman", "GuaguaSong" ],
			"Publisher" : "ituring.com.cn",
			"IsPublished" : true,
			"Price" : 9.99,
		}
	*/
	
	// 需要进行类型断言
	gobook, ok := r.(map[string]interface{})
	if ok {
		for k, v := range gobook {
			switch v2 := v.(type) {
				case string:
					fmt.Println(k, "is string", v2)
				case int:
					fmt.Println(k, "is int", v2)
				case bool:
					fmt.Println(k, "is bool", v2)
				case []interface{}:
					fmt.Println(k, "is an array:")
					for i, iv := range v2 {
						fmt.Println(i, iv)
					}
				default:
					fmt.Println(k, "is another type not handle yet")
			}
		}
	}
}