
package main

import (
	"fmt"
	"net"
	"os"
)

func main() {
	conn, err := net.Dial("udp", ":8888")
	if err != nil {
		fmt.Println("net.Dial err:", err)
		return
	}
	defer conn.Close()

	conn.Write([]byte("你好，我是用UDP的客户端"))

	go func() {
		str := make([]byte, 1024)
		for {
			n, err := os.Stdin.Read(str)	// 获取标准输入，发往服务端
			if err != nil {
				fmt.Println("os.Stdin. err =", err)
				return
			}
			conn.Write(str[:n])
		}
	}()

	buf := make([]byte, 1024)
	for {
		n, err1 := conn.Read(buf)		// 阻塞等待服务器发送过来的数据
		if err1 != nil {
			return
		}
		fmt.Println("服务器发来:", string(buf[:n]))
	}
}