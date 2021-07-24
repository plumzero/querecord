
package main

import (
	"fmt"
	"log"
	"net/rpc"
	"os"
	"strconv"
)

type ArgsTwo struct {
	X, Y int
}

func main() {
	client, err := rpc.DialHTTP("tcp", ":8888")
	if err != nil {
		log.Fatal("rpc.DialHTTP err:", err)
	}

	i1, _ := strconv.Atoi(os.Args[1])
	i2, _ := strconv.Atoi(os.Args[2])
	args := ArgsTwo{i1, i2}
	var reply int
	// 调用命名函数，等待它完成，并返回其错误状态
	err = client.Call("Algorithm.Sum", args, &reply)
	if err != nil {
		log.Fatal("Call Algorithm.Sum err:", err)
	}
	fmt.Printf("Algorithm 和为: %d+%d=%d\n", args.X, args.Y, reply)
}