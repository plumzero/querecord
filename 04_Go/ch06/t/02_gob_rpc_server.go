
package main

import (
	"fmt"
	"net/rpc"
	"net/http"
)

type Args struct {
	X, Y int
}

type Algorithm int

func (t *Algorithm) Sum(args *Args, reply *int) error {
	*reply = args.X + args.Y
	fmt.Println("Exec Sum ", *reply)
	return nil
}

func main() {
	// 实例化一个服务
	algorithm := new(Algorithm)
	fmt.Println("Algorithm start", algorithm)

	// 注册服务
	rpc.Register(algorithm)
	rpc.HandleHTTP()		// 通过 HTTP 显露服务接口

	err := http.ListenAndServe(":8888", nil)
	if err != nil {
		fmt.Println("http.ListenAndServe err:", err)
	}
}
