
package main

import (
	"fmt"
	"log"
	"net/rpc/jsonrpc"
)

type Send struct {
	Java, Go string
}

func main() {
	client, err := jsonrpc.Dial("tcp", ":8888")
	if err != nil {
		log.Fatal("Dial err:", err)
	}

	send := Send{"Java", "Go"}
	var receive string
	err = client.Call("Programmer.GetSkill", send, &receive)
	if err != nil {
		fmt.Println("Call err:", err)
	}
	fmt.Println("receive:", receive)
}