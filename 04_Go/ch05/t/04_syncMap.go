
package main

import (
	"fmt"
	"sync"
)

func main() {
	var m sync.Map

	// Store 保存数据
	m.Store("name", "Joe")
	m.Store("gender", "Male")

	// LoadOrStore
	// 若 key 不存在，则存入 key 和 value，返回 fasle 和输入的 value
	v, ok := m.LoadOrStore("name1", "Jim")
	fmt.Println(ok, v)	// false Jim

	// 若 key 已存在，则返回 true 和 key 对应的 value，不会修改原来的 value
	v, ok = m.LoadOrStore("name", "aaa")
	fmt.Println(ok, v)	// true Joe

	// Load 读取数据
	v, ok = m.Load("name")
	if ok {
		fmt.Println("key exist, value is ", v)
	} else {
		fmt.Println("key not exist")
	}

	// Range 遍历
	f := func(k, v interface{}) bool {
		fmt.Println(k, v)
		return true
	}
	m.Range(f)

	// Delete 删除 key 及数据
	m.Delete("name1")
	fmt.Println(m.Load("name1"))
}