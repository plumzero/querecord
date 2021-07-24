
package main

import (
	"fmt"
	"net"
	"net/rpc"
	"net/rpc/jsonrpc"
)

type ArgsLanguage struct {
	Java, Go string
}

type Programmer string

func (m *Programmer) GetSkill(al *ArgsLanguage, skill *string) error {
	*skill = "Skill1:" + al.Java + ", Skill2:" + al.Go
	return nil
}

func main() {
	str := new(Programmer)

	rpc.Register(str)

	tcpAddr, err := net.ResolveTCPAddr("tcp", ":8888")
	if err != nil {
		fmt.Println("ResolveTCPAddr err:", err)
		return
	}

	listener, err := net.ListenTCP("tcp", tcpAddr)
	if err != nil {
		fmt.Println("ListenTCP err:", err)
		return
	}

	for {
		conn, err := listener.Accept()
		if err != nil {
			continue
		}
		jsonrpc.ServeConn(conn)
	}
}